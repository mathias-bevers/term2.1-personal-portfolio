#include <cmath>
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <time.h>

#include "ball.h"
#include "core/physics/line.h"
#include "core/physics/lineCap.h"
#include "tools/settings.h"

#define PI 3.14159265

namespace personal_portfolio {
    Ball::Ball(std::function<void(int)> callback, GameScene& game_scene) :
        GameObject("ball.png", sf::Vector2f(WINDOW_WIDTH, WINDOW_HIGHT) * 0.5f), game_scene(game_scene)
    {
        srand(time(nullptr));
        on_score = callback;
        radius = get_size().x * 0.5f;
    }

    void Ball::update()
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            release_ball();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && DEBUG) {
            can_move = false;
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

            //TODO: increase on velocity on player hit.

            // Reflect velocity.
            const sf::Vector2f hit_normal = hit->get_normal();
            const float dot = (velocity.x * hit_normal.x) + (velocity.y * hit_normal.y);
            const sf::Vector2f reflection(velocity - (2 * dot * hit_normal));
            velocity = reflection;

            delete hit;
        }

        set_position(position);
    }

    void Ball::release_ball()
    {
        if (can_move) {
            return;
        }

        float angle = ((rand() % 450) / 100.0f) + 45;
        angle += (rand() % 2) == 0 ? 0 : 180;

        const float x = std::sin((angle * PI) / 180.0f);
        const float y = std::cos((angle * PI) / 180.0f);
        const float magintude = std::sqrt((x * x) + (y * y));
        const float scale = 1.0f / magintude;

        velocity = sf::Vector2f(x * scale, y * scale);
        velocity *= 0.25f;
        can_move = true;
    }

    const Hit* Ball::find_earliest_hit()
    {
        const Hit* line_hit = find_earliest_line();
        const Hit* cap_hit = find_earliest_cap();

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

                sf::Vector2f v = line->get_start() - get_position();
                float distance = (n.x * v.x) + (n.y * v.y);

                if (distance > radius) {
                    continue;
                }

                float toi = get_toi_line(line);
                sf::Vector2f poi = previous_position + (velocity * toi);
                sf::Vector2f relative_line = poi - line->get_start();
                sf::Vector2f line_difference = line->get_difference();
                line_difference *= (1.0f / std::sqrt((line_difference.x * line_difference.x) +
                                                     (line_difference.y * line_difference.y)));
                float projection =
                    (relative_line.x * line_difference.x + relative_line.y * line_difference.y);

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
        sf::Vector2f old_difference = previous_position - line->get_start();
        float a = ((normal.x * old_difference.x) + (normal.y * old_difference.y)) - radius;
        float b = -((normal.x * velocity.x) + (normal.y * velocity.y));

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