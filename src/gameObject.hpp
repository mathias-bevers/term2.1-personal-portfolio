#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

namespace personal_portfolio {
    class GameObject {
      public:
        sf::Vector2f position;
        sf::Vector2f size;

        GameObject(sf::Vector2f position, sf::Vector2f size);
        GameObject(sf::Vector2f size);
        GameObject();
        ~GameObject();
    };
}
#endif