#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <map>
#include <string>

#include "scene.h"

namespace personal_portfolio {
    class SceneManager {
      private:
        std::map<std::string, Scene*> scenes;
        Scene* active_scene;

        template <class T> T& reset_scene(T& scene)
        {
           return *new T();
        }

      public:
        SceneManager();
        ~SceneManager();

        void load_scene(std::string name);
        void register_scene(Scene& scene);

        Scene& get_active_scene() const;
    };
}
#endif