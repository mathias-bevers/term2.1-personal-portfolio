#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <concepts>
#include <map>
#include <string>

#include "scene.h"

namespace personal_portfolio {
    class SceneManager {
      private:
        Scene* active_scene;

      public:
        SceneManager();
        ~SceneManager();

        void load_scene(std::string name);

        Scene& get_active_scene() const;
    };
}
#endif