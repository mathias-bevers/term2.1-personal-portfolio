#include "calculator.hpp"

namespace personal_portfolio {

    Calculator::Calculator() { std::cout << "Calculator v0.1" << std::endl; }

    void Calculator::run() {
        std::cout << "1: add (+)" << std::endl;
        std::cout << "2: subtract (-)" << std::endl;
        std::cout << "3: multiply (*)" << std::endl;
        std::cout << "4: divide (/)" << std::endl;

        int choice = promptInt("Enter an operation a operation number");

        if(choice < 1 || choice > 4)
        {
            std::cout << "Choice needs to be between 1 and 4 and is: " << choice << std::endl;
            return;
        }

        int a = promptInt("Enter 1st number");
        int b = promptInt("Enter 2nd number");

        float result;
        char symbol;

        switch (choice) {
        case 1:
            result = add(a, b);
            symbol = '+';
            break;
        case 2:
            result = subtract(a, b);
            symbol = '-';
            break;
        case 3:
            result = multiply(a, b);
            symbol = '*';
            break;
        case 4:
            result = divide(a, b);
            symbol = '/';
            break;
        }

        std::cout << "There result of the equation \'" << a << symbol << b << "' = " << result << std::endl;
    }

    int Calculator::promptInt(std::string msg = "enter an integer > ") {
        std::string input;

        std::cout << msg << " > ";
        std::getline(std::cin, input);

        try {
            int i = std::stoi(input);
            return i;
        }
        catch (std::invalid_argument &e) {
            std::cout << "cannot convert \'" << input << "\' to int" << std::endl;
            return promptInt(msg);
        }
    }

    int Calculator::add(int a, int b) { return a + b; }
    int Calculator::subtract(int a, int b) { return a - b; }
    int Calculator::multiply(int a, int b) { return a * b; }
    float Calculator::divide(int a, int b) { return static_cast<float>(a) / b; }
}