#include "gameObject.h"
#include "../tools/easylogging++.h"
#include "../tools/settings.h"

namespace personal_portfolio {
    GameObject::GameObject(std::string sprite_path) : GameObject::GameObject(sprite_path, sf::Vector2f(0, 0))
    {
    }

    GameObject::GameObject(std::string sprite_path, sf::Vector2f position)
    {
        this->sprite_path = PATH_IMAGES + sprite_path;
        if (!texture.loadFromFile(this->sprite_path)) {
            std::string cwd = get_working_dir();

            if (!cwd.empty()) {
                LOG(ERROR) << "Could not load texture with path: " << cwd << "/" << sprite_path;
            }
            else {
                LOG(ERROR) << "Could not load image or path";
            }

            exit(1);
            return;
        }

        sprite = sf::Sprite(texture);
        sprite.setOrigin(sf::Vector2f(texture.getSize()) * 0.5f);
        this->position = position;
    }

    void GameObject::render(sf::RenderWindow& window) const { window.draw(sprite); }

    void GameObject::update() { sprite.setPosition(position); }

    sf::Vector2f GameObject::get_size() const
    {
        const float x = sprite.getTexture()->getSize().x * sprite.getScale().x;
        const float y = sprite.getTexture()->getSize().y * sprite.getScale().y;
        return sf::Vector2f(x, y);
    }

    void GameObject::set_size(const sf::Vector2f size)
    {
        sf::Vector2f scale(1, 1);
        scale.x = size.x / sprite.getTexture()->getSize().x;
        scale.y = size.y / sprite.getTexture()->getSize().y;
        sprite.setScale(scale);
    }

    const sf::Vector2f GameObject::get_position() const { return position; }

    void GameObject::set_position(const sf::Vector2f position) { this->position = position; }

    const sf::Color GameObject::get_color() const { return sprite.getColor(); }

    void GameObject::set_color(const sf::Color color) { sprite.setColor(color); }

    std::ostream& operator<<(std::ostream& stream, GameObject const& game_object)
    {
        stream << game_object.sprite_path << std::endl;
        stream << "\tposition: " << game_object.get_position() << std::endl;
        stream << "\tsize: " << game_object.get_size() << std::endl;
        stream << "\torigin: " << game_object.sprite.getOrigin() << std::endl;
        return stream;
    }

    GameObject::~GameObject() = default;
}