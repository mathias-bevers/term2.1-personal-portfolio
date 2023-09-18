#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>

#include "SFML/Graphics.hpp"
#include "gameObject.h"

namespace personal_portfolio {
    class Scene {
      private:
        std::string name;

      protected:
        std::vector<GameObject*> game_objects;

      public:
        Scene(std::string name);
        virtual ~Scene();

        virtual void update();
        virtual void render(sf::RenderWindow& window);

        const std::string get_name() const;
    };
}
#endif