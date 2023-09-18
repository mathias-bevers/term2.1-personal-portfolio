#ifndef GAME_H
#define GAME_H

#include <vector>

#include "player.h"

namespace personal_portfolio {
    /// @brief Main loop of the game.
    class Game {
      private:
        sf::RenderWindow window;
        std::vector<GameObject*> game_objects;

        void update();
        void render();

      public:
        static Game* instance;

        Game();
        ~Game();
        void start();
        void close();
        sf::RenderWindow& get_window();
    };
}

#endif