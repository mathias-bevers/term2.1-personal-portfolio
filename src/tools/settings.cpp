#include <limits.h>
#include <unistd.h>

#include "settings.hpp"

namespace personal_portfolio {
    

    std::string getWorkingDir() {
        char cwd[PATH_MAX];

        if (getcwd(cwd, sizeof(cwd)) != nullptr) {
            return std::string(cwd);
        }

        return std::string();
    }
}