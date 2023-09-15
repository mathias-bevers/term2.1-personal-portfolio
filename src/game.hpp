#ifndef GAME_H
#define GAME_H

#include "player.hpp"

namespace personal_portfolio {

    /// @brief Main loop of the game.
    class Game {
      private:
        sf::RenderWindow window;
        Player player;

        void update();

      public:
        static Game* instance;

        Game();
        ~Game();
        void start();
        void close();
        sf::RenderWindow& getWindow();
    };
}

#endif