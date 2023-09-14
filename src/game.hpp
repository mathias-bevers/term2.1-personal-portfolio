#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "tools/easylogging++.h"

namespace personal_portfolio {

    /// @brief Main loop of the game.
    class Game {
      private:
        sf::RenderWindow window;
        sf::CircleShape circle;

        void update();

      public:
        Game();
        ~Game();
        void start();
    };
}

#endif