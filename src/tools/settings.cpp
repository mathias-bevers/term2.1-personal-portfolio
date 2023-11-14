#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <unistd.h>

#include "settings.h"

namespace personal_portfolio {
    bool DEBUG = false;

    std::string get_working_dir()
    {
        char cwd[PATH_MAX];

        if (getcwd(cwd, sizeof(cwd)) != nullptr) {
            return std::string(cwd);
        }

        return std::string();
    }

    std::ostream& operator<<(std::ostream& stream, sf::Vector2f const& v)
    {
        stream << std::fixed;
        stream << "[" << std::setprecision(v.x) << "," << std::setprecision(v.y) << "]";
        return stream;
    }
}