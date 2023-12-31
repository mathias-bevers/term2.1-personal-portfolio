#include "sceneManager.h"
#include "../tools/SuperFactory.h"
#include "../tools/easylogging++.h"

namespace personal_portfolio {
    SceneManager::SceneManager() { active_scene = nullptr; }

    Scene& SceneManager::get_active_scene() const { return *active_scene; }

    void SceneManager::load_scene(std::string name)
    {
        if (active_scene != nullptr) {
            active_scene->await_destroy();
        }

        if (!SuperFactory::Create(name, active_scene)) {
            LOG(ERROR) << "Could not load scene with name: " << name;
            exit(1);
        }

        active_scene->set_name();
        LOG(INFO) << "Loaded scene: " << get_active_scene();
    }

    SceneManager::~SceneManager()
    {
        delete active_scene;
        active_scene = nullptr;
    }
}