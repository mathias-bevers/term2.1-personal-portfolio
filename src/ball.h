#ifndef BALL_H
#define BALL_H

#include "core/gameObject.h"

namespace personal_portfolio {
    class Ball : public GameObject {
      public:
        Ball();
        ~Ball();
        
        void update() override;

      private:
        sf::Vector2f velocity;

        void move();
    };
}
#endif