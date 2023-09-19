#include "sceneManager.h"
#include "../tools/easylogging++.h"
#include "../tools/SuperFactory.h"

namespace personal_portfolio {
    SceneManager::SceneManager() = default;

    Scene& SceneManager::get_active_scene() const { return *active_scene; }

    void SceneManager::load_scene(std::string name)
    {
        delete active_scene;

        if(!SuperFactory::Create(name, active_scene))
        {
            LOG(ERROR) << "Could not load scene with name: " << name;
            exit(1);
        }

        active_scene->start();
        LOG(INFO) << "Loaded scene: " << active_scene;
    }

    SceneManager::~SceneManager()
    {
        delete active_scene;
        active_scene = nullptr;
    }
}