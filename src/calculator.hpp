#include <iostream>
#include <string>

namespace personal_portfolio {
    class Calculator {
      public:
        Calculator();
        void run();

      private:
        int promptInt(std::string msg);

        int add(int a, int b);
        int subtract(int a, int b);
        int multiply(int a, int b);
        float divide(int a, int b);
    };
}