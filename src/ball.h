#ifndef BALL_H
#define BALL_H

#include <functional>
#include <vector>

#include "core/gameObject.h"
#include "core/physics/hit.h"
#include "core/physics/line.h"
#include "scenes/gameScene.h"

namespace personal_portfolio {
    class Ball : public GameObject {
      public:
        Ball(std::function<void(int)> callback, GameScene& game_scene);
        ~Ball();

        void update() override;

      private:
        GameScene& game_scene;
        std::function<void(int)> on_score;
        sf::Vector2f previous_position;
        sf::Vector2f velocity;
        bool can_move = false;
        float radius;

        void move();
        void release_ball();
        void score(int scorer_id);

        const Hit* find_earliest_hit();
        const Hit* find_earliest_line();
        const Hit* find_earliest_cap();
        const float get_toi_line(Line* line);
    };
}
#endif