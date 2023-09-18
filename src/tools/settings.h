#ifndef SETTINGS_H
#define SETTINGS_H
#include <string>

namespace personal_portfolio {
    const std::string PATH_ASSETS = "assets/";
    const std::string PATH_IMAGES = PATH_ASSETS + "images/";
    const std::string PATH_FONTS = PATH_ASSETS + "fonts/";
    const std::string PATH_SOUNDS = PATH_ASSETS + "sounds/";

    std::string get_working_dir();
}
#endif