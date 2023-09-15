#include <iostream>
#include <limits>
#include "src/game.hpp"
#include "src/tools/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

namespace pp = personal_portfolio;

int main(int argc, char *argv[]) {
    std::cout << "Mathias Bevers personal portfolio 1" << std::endl;

    pp::Game game;
    game.start();
    
    return 0;
}