#include <cmath>
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <time.h>

#include "ball.h"
#include "core/physics/line.h"
#include "core/physics/lineCap.h"
#include "tools/settings.h"

namespace personal_portfolio {
    Ball::Ball(std::function<void(int)> callback, GameScene& game_scene) :
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
        GameObject::update();

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

        previous_position = get_position();
        sf::Vector2 position = get_position() + velocity;

        // Find earliest collision, cap or line.
        const Hit* hit = find_earliest_hit();
        if (hit != nullptr) {
            // Move to hit postion by velocity * time of impact;
            position = previous_position + velocity * hit->get_toi();

            float bounciness = 1.0f;
            // TODO: increase velocity if hit is player.

            // Reflect velocity.
            const sf::Vector2f hit_normal = hit->get_normal();
            const float dot = (velocity.x * hit_normal.x) + (velocity.x * hit_normal.y);
            const float factor = (-1.0f - bounciness) * dot;
            velocity =
                sf::Vector2f((factor * hit_normal.x) + velocity.x, (factor * hit_normal.y) + velocity.y);

            delete hit;
        }

        set_position(position);
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

    const Hit* Ball::find_earliest_hit()
    {
        const Hit* line_hit = find_earliest_line();
        const Hit* cap_hit = find_earliest_hit();

        if (line_hit == nullptr && cap_hit == nullptr) {
            return nullptr;
        }

        if (line_hit != nullptr && cap_hit == nullptr) {
            return line_hit;
        }
        if (line_hit == nullptr && cap_hit != nullptr) {
            return cap_hit;
        }

        return line_hit->get_toi() < cap_hit->get_toi() ? line_hit : cap_hit;
    }

    const Hit* Ball::find_earliest_line()
    {
        float t = std::numeric_limits<float>::infinity();
        Hit* hit = nullptr;

        for (size_t i = 0; i < game_scene.get_physics_objects().size(); ++i) {
            if (Line* line = dynamic_cast<Line*>(game_scene.get_physics_objects().at(i))) {
                sf::Vector2f n = line->get_normal();

                // manual n.dot(line_start - position).
                float distance = (n.x * (line->get_start().x - get_position().x)) +
                                 (n.y * (line->get_start().y - get_position().y));

                if (distance > radius) {
                    continue;
                }

                float toi = get_toi_line(line);

                sf::Vector2f poi = previous_position + (velocity * toi);
                sf::Vector2f relative_line = poi - line->get_start();
                float projection = (relative_line.x * n.x) + (relative_line.y * n.y);

                if (projection > 0 && projection < line->get_magnitude()) {
                    if (toi < t) {
                        Hit* h = new Hit(n, *line, toi);
                        delete hit;
                        hit = h;
                        t = toi;
                    }
                }
            }
        }

        return hit;
    }

    const Hit* Ball::find_earliest_cap()
    {
        float t = std::numeric_limits<float>::infinity();
        Hit* hit = nullptr;

        for (size_t i = 0; i < game_scene.get_physics_objects().size(); ++i) {
            if (LineCap* cap = dynamic_cast<LineCap*>(game_scene.get_physics_objects().at(i))) {
                sf::Vector2f difference = get_position() - cap->get_postion();
                float distance = sqrt((difference.x * difference.x) + (difference.y * difference.y));
                float min_radius = radius + cap->get_radius();

                if (distance > min_radius) {
                    continue;
                }

                sf::Vector2f normal = difference * (1.0f / distance);
                float over_lap = (radius + cap->get_radius()) - distance;
                sf::Vector2f poi = get_position() + (normal * over_lap);
                sf::Vector2f a = poi - previous_position;
                float toi = sqrt((a.x * a.x) + (a.y * a.y)) /
                            sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));

                if (toi < t) {
                    Hit* h = new Hit(normal, *cap, toi);
                    delete hit;
                    hit = h;
                    t = toi;
                }
            }
        }

        return hit;
    }

    const float Ball::get_toi_line(Line* line)
    {
        sf::Vector2f normal = line->get_normal();
        sf::Vector2f old_difference = line->get_start() - previous_position;
        float a = ((normal.x * old_difference.x) + (normal.y * old_difference.y)) - radius;
        float b = (normal.x * velocity.x) + (normal.y * velocity.y);

        if (b < 0) {
            return std::numeric_limits<float>::infinity();
        }

        if (a > 0) {
            float t = a / b;
            if (t < 1.0f) {
                return t;
            }
        }
        else if (a > -radius) {
            return 0;
        }

        return std::numeric_limits<float>::infinity();
    }

    void Ball::score(int scorer_id)
    {
        can_move = false;
        set_position(sf::Vector2f(WINDOW_WIDTH, WINDOW_HIGHT) * 0.5f);
        on_score(scorer_id);
    }

    Ball::~Ball() = default;
}