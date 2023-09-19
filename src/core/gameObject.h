#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <string>

namespace personal_portfolio {
    class GameObject {
        std::string sprite_path;
        sf::Texture texture;
        sf::Sprite sprite;

      public:
        GameObject(std::string sprite_path, sf::Vector2f position);
        GameObject(std::string sprite_path);
        ~GameObject();

        void render(sf::RenderWindow& window) const;
        virtual void update();

        sf::Vector2f get_size() const;
        void set_size(const sf::Vector2f size);

        const sf::Vector2f get_position() const;
        void set_position(const sf::Vector2f position);

        const sf::Color get_color() const;
        void set_color(const sf::Color color);
    };
}
#endif