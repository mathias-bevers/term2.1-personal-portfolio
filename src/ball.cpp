#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "ball.h"
#include "tools/settings.h"

namespace personal_portfolio {
    Ball::Ball(std::function<void(int)> callback) : GameObject("ball.png", sf::Vector2f(WINDOW_WIDTH * 0.5f, WINDOW_HIGHT * 0.5f))
    {
        srand(time(nullptr));

        float x = (rand() % 200 - 100) / 100.0f;
        float y = (rand() % 200 - 100) / 100.0f;
        velocity = sf::Vector2f(x, y) * 0.25f;

        on_score = callback;
    }

    void Ball::update()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            can_move = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
            on_score(rand() % 2);
        }

        move();
    }

    void Ball::move()
    {
        if (!can_move) {
            return;
        }

        sf::Vector2f previous_position = get_position();
        sf::Vector2 position = get_position() + velocity;

        // Find earliest collision, cap or line.
        // Move to hit postion by velocity * time of impact;
        // Reflect velocity.
    }

    Ball::~Ball() = default;
}