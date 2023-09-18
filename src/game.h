#ifndef GAME_H
#define GAME_H

#include <vector>

#include "core/sceneManager.h"

namespace personal_portfolio {
    /// @brief Main loop of the game.
    class Game {
      private:
        sf::RenderWindow window;
        SceneManager scene_manager;

        void update();
        void render();

      public:
        static Game* instance;

        Game();
        ~Game();
        void start();
        void close();

        SceneManager& get_scene_manager() const;
    };
}

#endif