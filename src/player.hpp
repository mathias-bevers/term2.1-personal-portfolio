#ifndef PLAYER_H
#define PLAYER_H

#include<string>

#include "gameObject.hpp"

namespace personal_portfolio {
    class Player : public GameObject {
      private:
        sf::Texture texture;
        sf::Sprite sprite;

      public:
        Player(std::string spritePath);
        ~Player();

        void update();
        sf::Sprite& getSprite();
    };
}
#endif