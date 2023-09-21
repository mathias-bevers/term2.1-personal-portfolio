#include <sstream>

#include "../tools/SuperFactory.h"
#include "../tools/easylogging++.h"
#include "scene.h"

namespace personal_portfolio {
    SF_Register_Type(SF_Abstract, Scene);
    Scene::Scene() { }

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

    std::ostream& operator<<(std::ostream& stream, Scene const& scene)
    {
        stream << typeid(scene).name() << std::endl;
        for (size_t i = 0; i < scene.game_objects.size(); ++i) {
            stream << "\t" << typeid(scene.game_objects.at(i)).name();

            if (i < scene.game_objects.size() - 1) {
                stream << std::endl;
            }
        }
        
        return stream;
    }

    Scene::~Scene()
    {
        for (size_t i = 0; i < game_objects.size(); ++i) {
            GameObject* game_object = game_objects.at(i);
            delete game_object;
        }

        game_objects.clear();
        LOG(INFO) << "Offloaded scene: " << typeid(this).name();
    }
}