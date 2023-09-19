#include <stdlib.h>
#include <time.h>

#include "ball.h"
#include "tools/settings.h"

namespace personal_portfolio {
    Ball::Ball() : GameObject("ball.png")
    {
        srand(time(nullptr));

        set_position(sf::Vector2f(WINDOW_WIDTH * 0.5f, WINDOW_HIGHT * 0.5f));

        float x = (rand() % 200 - 100) / 100.0f;
        float y = (rand() % 200 - 100) / 100.0f;
        velocity = sf::Vector2f(x, y);

        set_size(sf::Vector2f(75, 75));
    }

    void Ball::update() { move(); }

    void Ball::move()
    {
        sf::Vector2 newPosition = get_position() + velocity;
        set_position(newPosition);
    }

    Ball::~Ball() = default;
}