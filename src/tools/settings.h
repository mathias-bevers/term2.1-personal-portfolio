#ifndef SETTINGS_H
#define SETTINGS_H
#include <string>
#include <SFML/Graphics.hpp>

namespace personal_portfolio {
    const std::string PATH_ASSETS = "assets/";
    const std::string PATH_IMAGES = PATH_ASSETS + "images/";
    const std::string PATH_FONTS = PATH_ASSETS + "fonts/";
    const std::string PATH_SOUNDS = PATH_ASSETS + "sounds/";

    const int WINDOW_WIDTH = 1600;
    const int WINDOW_HIGHT = 1000;
    const int WIN_SCORE = 5;

    extern bool DEBUG;

    std::string get_working_dir();
}
#endif