#include <cmath>

#include "game.h"
#include "player.h"
#include "tools/easylogging++.h"
#include "tools/settings.h"

namespace personal_portfolio {
    Player::Player(std::string sprite_path) : GameObject(sprite_path) { 
        set_size(sf::Vector2f(500,500));
    }

    void Player::update() {
        sf::Vector2f input;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            input.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            input.y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            input.x -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            input.x += 1;
        }

        float magnitude = (input.x * input.x) + (input.y * input.y);
        magnitude = sqrt(magnitude);
        if (magnitude != 0.0f) {
            input *= 1.0f / magnitude;
        }

        move(input);
    }

    void Player::move(const sf::Vector2f velocity)
    {
        const sf::Vector2f newPosition = get_position() + velocity;
        set_position(newPosition);
    }

    Player::~Player() = default;
}