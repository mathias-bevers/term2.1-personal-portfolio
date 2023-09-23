#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "ball.h"
#include "tools/settings.h"

namespace personal_portfolio {
    Ball::Ball(std::function<void(int)> callback, GameScene& gameScene) :
        GameObject("ball.png", sf::Vector2f(WINDOW_WIDTH, WINDOW_HIGHT) * 0.5f), game_scene(game_scene)
    {
        srand(time(nullptr));
        on_score = callback;
    }

    void Ball::update()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            release_ball();
        }

        move();

        float x_position = get_position().x;
        if (x_position < 0) {
            score(1);
        }
        else if (x_position > WINDOW_WIDTH) {
            score(0);
        }
    }

    void Ball::move()
    {
        if (!can_move) {
            return;
        }

        sf::Vector2f previous_position = get_position();
        sf::Vector2 position = get_position() + velocity;
        set_position(position);

        // Find earliest collision, cap or line.
        // Move to hit postion by velocity * time of impact;
        // Reflect velocity.
    }

    void Ball::release_ball()
    {
        if (can_move) {
            return;
        }

        const float x = (rand() % 200 - 100) / 100.0f;
        const float y = (rand() % 200 - 100) / 100.0f;
        const float magintude = std::sqrt((x * x) + (y * y));
        const float scale = 1.0f / magintude;

        velocity = sf::Vector2f(x * scale, y * scale);
        velocity *= 0.25f;
        can_move = true;
    }

    void Ball::score(int scorer_id)
    {
        can_move = false;
        set_position(sf::Vector2f(WINDOW_WIDTH, WINDOW_HIGHT) * 0.5f);
        on_score(scorer_id);
    }

    Ball::~Ball() = default;
}