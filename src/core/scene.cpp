#include <sstream>

#include "../tools/SuperFactory.h"
#include "../tools/easylogging++.h"
#include "scene.h"

namespace personal_portfolio {
    SF_Register_Type(SF_Abstract, Scene);
    Scene::Scene() { }

    void Scene::update()
    {
        for(size_t i = 0; i < game_objects.size(); ++i){
            game_objects.at(i)->update();
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
        stream << typeid(scene).name();
        return stream;
    }

    Scene::~Scene()
    {
        for (size_t i = 0; i < game_objects.size(); ++i) {
            delete game_objects.at(i);
        }

        game_objects.clear();
        LOG(INFO) << "Offloaded scene: " << typeid(this).name();
    }
}