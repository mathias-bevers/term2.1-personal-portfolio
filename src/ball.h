#ifndef BALL_H
#define BALL_H

#include <functional>

#include "core/gameObject.h"
#include "scenes/gameScene.h"

namespace personal_portfolio {
    class Ball : public GameObject {
      public:
        Ball(std::function<void(int)> callback, GameScene& game_scene);
        ~Ball();
        
        void update() override;

      private:
        const GameScene& game_scene;
        std::function<void(int)> on_score;
        sf::Vector2f velocity;
        bool can_move = false; 
        int radius;


        void move();
        void release_ball();
        void score(int scorer_id);
    };
}
#endif