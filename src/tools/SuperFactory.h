
// Copyright (c) 2009 Francis Xavier Joseph Pulikotil
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef FACTORY_HEADER
#define FACTORY_HEADER

#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

// Macros which specify whether a class is Concrete (creatable) or Abstract (non-creatable).
#define SF_Concrete
#define SF_Abstract , 0

// Macros to register a product and its base classes (if any)
#define SF_Register_Type(AC,X)                      const bool ANONYMOUS = SuperFactory::Register<X>( #X AC )
#define SF_Register_Type_Base1(AC,X,B1)             SF_Register_Type(AC,X)                   && SuperFactory::RegisterBase<X, B1>()
#define SF_Register_Type_Base2(AC,X,B1,B2)          SF_Register_Type_Base1(AC,X,B1)          && SuperFactory::RegisterBase<X, B2>()
#define SF_Register_Type_Base3(AC,X,B1,B2,B3)       SF_Register_Type_Base2(AC,X,B1,B2)       && SuperFactory::RegisterBase<X, B3>()
#define SF_Register_Type_Base4(AC,X,B1,B2,B3,B4)    SF_Register_Type_Base3(AC,X,B1,B2,B3)    && SuperFactory::RegisterBase<X, B4>()
#define SF_Register_Type_Base5(AC,X,B1,B2,B3,B4,B5) SF_Register_Type_Base4(AC,X,B1,B2,B3,B4) && SuperFactory::RegisterBase<X, B5>()

// Note: For any class X, with [n] number of base classes, the series goes like this:
// #define SF_Register_Type_Base[n](AC,X,B1,B2,...,B[n]) SF_Register_Type_Base[n-1](AC,X,B1,B2,...,B[n-1]) && SuperFactory::RegisterBase<X, B[n]>()

// Macro to generate a unique variable name based on the line number
#define ANONYMOUS       JOIN1(anonymous,__LINE__)
#define JOIN1(N1,N2)    JOIN2(N1,N2)
#define JOIN2(N1,N2)    N1##N2

namespace SuperFactory {

// Compile-time type-equality checking.
template <class T, class U> struct IsSameType { enum { result = false }; };
template <class T> struct IsSameType<T,T> { enum { result = true }; };

// Compile time assertion.
template <bool> class CompileTimeChecker;
template <> class CompileTimeChecker<true> { };

// Factory for all objects of type Product
template <class Product, typename Identifier = std::string>
class Factory
{
public:
    typedef Product *const (*Creator) ();

private:
    Identifier _identifier;
    Creator    _creator;
    bool       _bRegistered;

    typedef Product *const (*DerivedCreator) (const Identifier &);
    typedef std::vector<DerivedCreator> DerivedCreators;
    DerivedCreators _derivedCreators;

// Singleton
private:
    // Constructor / Destructor
    explicit Factory() : _bRegistered( false ) { }
    ~Factory() { }

    // Copy Constructor / Assignment Operator
    Factory(const Factory &);
    const Factory &operator =(const Factory &);

private:
    template <class T>
    static Product *const CreateDerived(const Identifier &identifier)
    {
        return Factory<T, Identifier>::Instance().Create( identifier );
    }

public:
    // Singleton instance access
    static Factory<Product, Identifier> &Instance()
    {
        static Factory<Product, Identifier> factory;
        return factory;
    }

    static Product *const DefaultCreator()
    {
        return new Product();
    }

    const bool Register(const Identifier &identifier, const Creator creator)
    {
        // Note: If the creator parameter is null, then this product is abstract.

        // Run-time check for multiple registrations
        assert( (!_bRegistered) );

        _identifier  = identifier;
        _creator     = creator;
        _bRegistered = true;

        return true;
    }

    template <class T>
    const bool RegisterDerived()
    {
        // Compile-time check that the derived type is not the same as this type
        (void)sizeof( CompileTimeChecker< !IsSameType<T, Product>::result > );

        const DerivedCreator derivedCreator = CreateDerived<T>;

        // Run-time check for duplicate registrations
        assert( (std::find( _derivedCreators.begin(), _derivedCreators.end(), derivedCreator ) == _derivedCreators.end()) );

        _derivedCreators.push_back( derivedCreator );
        return true;
    }

    Product *const Create(const Identifier &identifier)
    {
        // If it's this product itself, then create it.
        if( _identifier == identifier )
            return (_creator)? (_creator()): (0);

        // See if it's a derived product
        for(typename DerivedCreators::const_iterator itr = _derivedCreators.begin(); itr != _derivedCreators.end(); ++itr)
        {
            Product *const pProduct = (*itr)( identifier );
            if( pProduct )
                return pProduct;
        }

        // It's either an ancestor product, or an unrelated product.
        return 0;
    }
};

// Helper functions for Factories with std::string identifier types.

// Registers an identifier and a creator with a Product
template <class Product>
const bool Register(const std::string &identifier, const typename Factory<Product>::Creator creator = Factory<Product>::DefaultCreator)
{
    return Factory<Product>::Instance().Register( identifier, creator );
}

// Registers a Product's base class
template <class Product, class ProductBase>
const bool RegisterBase()
{
    return Factory<ProductBase>::Instance().template RegisterDerived<Product>();
}

// Creates an object of type Product, given a product identifier
template <class T>
const bool Create(const std::string &identifier, T* &pProduct)
{
    pProduct = Factory<T>::Instance().Create( identifier );
    return (pProduct != 0);
}

} // namespace SuperFactory

#endif
