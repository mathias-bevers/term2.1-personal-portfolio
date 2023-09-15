#include <cmath>

#include "game.hpp"
#include "player.hpp"
#include "tools/easylogging++.h"
#include "tools/settings.hpp"

namespace personal_portfolio {
    Player::Player(std::string spritePath) : GameObject(sf::Vector2f(500, 500)) {
        if (!texture.loadFromFile(PATH_IMAGES + spritePath)) {
            std::string cwd = getWorkingDir();

            if (!cwd.empty()) {
                LOG(ERROR) << "Could not load texture with path: " << cwd << "/" << spritePath;
            }
            else {
                LOG(ERROR) << "Could not load image or path";
            }

            exit(0);
            return;
        }

        sprite.setTexture(texture);
        sf::Vector2u textureSize = texture.getSize();
        sprite.setScale((500.0f / textureSize.x), (500.0f / textureSize.y));
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

        position += input;
        sprite.setPosition(position);
    }

    sf::Sprite& Player::getSprite() {
        return sprite;
    }

    Player::~Player() = default;
}