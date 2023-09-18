#include "scene.h"
#include "../tools/easylogging++.h"

namespace personal_portfolio {
    Scene::Scene(std::string name)
    {
        this->name = name;
        LOG(INFO) << "Loaded scene: " << this->name;
    }

    void Scene::update()
    {
        for (GameObject* game_object : game_objects) {
            game_object->update();
        }
    }

    void Scene::render(sf::RenderWindow& window)
    {
        for (GameObject* game_object : game_objects) {
            game_object->render(window);
        }
    }

    const std::string Scene::get_name() const { return name; }

    Scene::~Scene()
    {
        for (int i = 0; i < game_objects.size(); ++i) {
            GameObject* game_object = game_objects.at(i);
            delete game_object;
        }

        game_objects.clear();
        LOG(INFO) << "Offloaded scene: " << name;
    }
}