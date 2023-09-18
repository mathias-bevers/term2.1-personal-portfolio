#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "gameObject.h"

namespace personal_portfolio {
    class Player : public GameObject {
      public:
        Player(std::string sprite_path);
        ~Player();

        void update() override;

      private:
        void move(const sf::Vector2f velocity);
    };
}
#endif