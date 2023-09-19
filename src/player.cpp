#include <cmath>
#include <stdexcept>

#include "game.h"
#include "player.h"
#include "tools/easylogging++.h"
#include "tools/settings.h"

namespace personal_portfolio {
    Player::Player(int id) : GameObject("player.png")
    {
        set_size(sf::Vector2f(35, 250));

        if (id < 0 || id > 1) {
            throw std::out_of_range("id needs to be 0 or 1");
        }

        up = (id == 0) ? sf::Keyboard::W : sf::Keyboard::Up;
        down = (id == 0) ? sf::Keyboard::S : sf::Keyboard::Down;

        float x = WINDOW_WIDTH * ((id == 0) ? 0.1f : 0.9f);
        float y = WINDOW_HIGHT * 0.5f;
        set_position(sf::Vector2f(x, y));
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
    }

    void Player::move(const sf::Vector2f velocity)
    {
        sf::Vector2f newPosition = get_position() + velocity;
        newPosition.y = std::clamp(newPosition.y, get_size().y * 0.5f, WINDOW_HIGHT - get_size().y * 0.5f);
        set_position(newPosition);
    }

    Player::~Player() = default;
}