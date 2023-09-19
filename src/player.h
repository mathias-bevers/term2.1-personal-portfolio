#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "core/gameObject.h"

namespace personal_portfolio {
    class Player : public GameObject {
      public:
        Player(int id);
        ~Player();

        void update() override;

      private:
        sf::Keyboard::Key up;
        sf::Keyboard::Key down;
        const float move_speed = 0.35f;

        void move(const sf::Vector2f velocity);
    };
}
#endif