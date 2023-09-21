#ifndef BALL_H
#define BALL_H

#include <functional>

#include "core/gameObject.h"

namespace personal_portfolio {
    class Ball : public GameObject {
      public:
        Ball(std::function<void(int)> callback);
        ~Ball();
        
        void update() override;
      private:
        std::function<void(int)> on_score;
        sf::Vector2f velocity;
        bool can_move = false; 
        int radius;


        void move();
    };
}
#endif