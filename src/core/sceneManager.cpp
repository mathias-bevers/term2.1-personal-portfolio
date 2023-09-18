#include "sceneManager.h"
#include "../tools/easylogging++.h"

namespace personal_portfolio {
    SceneManager::SceneManager() = default;

    Scene& SceneManager::get_active_scene() const { return *active_scene; }

    void SceneManager::load_scene(std::string name)
    {
        LOG(INFO) << "Before";

        scenes[name];

        LOG(INFO) << "After";

        active_scene = scenes[name];
    }

    void SceneManager::register_scene(Scene& scene)
    {
        this->scenes.emplace(scene.get_name(), &scene);

        if (scenes.size() > 1) {
            return;
        }

        load_scene(scene.get_name());
    }

    SceneManager::~SceneManager()
    {
        delete active_scene;
        active_scene = nullptr;
    }
}