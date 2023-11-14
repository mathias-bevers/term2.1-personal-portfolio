#include "src/game.h"
#include "src/tools/easylogging++.h"
#include "src/tools/settings.h"
#include <iostream>
#include <limits>

INITIALIZE_EASYLOGGINGPP

namespace pp = personal_portfolio;

bool DEBUG;

int main(int argc, char* argv[])
{
    std::cout << "Mathias Bevers personal portfolio 1" << std::endl;

    if (argc > 1) {
        for (int i = 0; i < argc; ++i) {
            if(strcmp(argv[i], "--debug") == 0 || strcmp(argv[i], "-d") == 0){
                pp::DEBUG = true;
                LOG(INFO) << "DEBUG ENABLED!";
            }
        }
    }

    pp::Game game;
    game.start();

    return 0;
}