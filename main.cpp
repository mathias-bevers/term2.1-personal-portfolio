#include <iostream>
#include <limits>

#include "src/calculator.hpp"

int main() {
    std::cout << "Mathias Bevers personal portfolio 1\n\n";

    personal_portfolio::Calculator calculator;
    calculator.run();

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    

    return 0;
}