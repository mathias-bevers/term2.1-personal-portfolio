#include <limits.h>
#include <unistd.h>

#include "settings.h"

namespace personal_portfolio {
    std::string get_working_dir()
    {
        char cwd[PATH_MAX];

        if (getcwd(cwd, sizeof(cwd)) != nullptr) {
            return std::string(cwd);
        }
        
        return std::string();
    }
}