#include <cmath>
#include <stdexcept>

#include "core/physics/line.h"
#include "core/physics/lineCap.h"
#include "game.h"
#include "player.h"
#include "tools/settings.h"

namespace personal_portfolio {
    Player::Player(int id) : GameObject("player.png"), id(id)
    {
        const sf::Vector2f size(35, 250);
        set_size(size);

        if (this->id < 0 || this->id > 1) {
            throw std::out_of_range("id needs to be 0 or 1");
        }

        up = (this->id == 0) ? sf::Keyboard::W : sf::Keyboard::Up;
        down = (this->id == 0) ? sf::Keyboard::S : sf::Keyboard::Down;

        float x = WINDOW_WIDTH * ((this->id == 0) ? 0.1f : 0.9f);
        float y = WINDOW_HIGHT * 0.5f;
        set_position(sf::Vector2f(x, y));

        const sf::Vector2f halfSize = size * 0.5f;
        physics_objects.push_back(new Line(halfSize.x, -halfSize.y, -halfSize.x, -halfSize.y, this));
        physics_objects.push_back(new Line(-halfSize.x, halfSize.y, halfSize.x, halfSize.y, this));
        physics_objects.push_back(new Line(halfSize.x, halfSize.y, halfSize.x, -halfSize.y, this));
        physics_objects.push_back(new Line(-halfSize.x, -halfSize.y, -halfSize.x, halfSize.y, this));
        physics_objects.push_back(new LineCap(0, halfSize, this));
        physics_objects.push_back(new LineCap(0, -halfSize, this));
        physics_objects.push_back(new LineCap(0, halfSize.x, -halfSize.y, this));
        physics_objects.push_back(new LineCap(0, -halfSize.x, halfSize.y, this));
    }

    void Player::update()
    {
        sf::Vector2f input;
        if (sf::Keyboard::isKeyPressed(up)) {
            input.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(down)) {
            input.y += 1;
        }

        move(input * move_speed);
        GameObject::update();
    }

    const std::vector<PhysicsObject*>& Player::get_physics_objects() const { return physics_objects; }

    void Player::move(const sf::Vector2f velocity)
    {
        sf::Vector2f newPosition = get_position() + velocity;
        newPosition.y = std::clamp(newPosition.y, get_size().y * 0.5f, WINDOW_HIGHT - get_size().y * 0.5f);
        set_position(newPosition);
    }

    Player::~Player() = default;
}