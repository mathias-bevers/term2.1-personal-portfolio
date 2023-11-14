#ifndef GAME_H
#define GAME_H

#include <vector>

#include "core/sceneManager.h"

namespace personal_portfolio {
    /// @brief Main loop of the game.
    class Game {
      private:
        sf::RenderWindow window;
        SceneManager* scene_manager;
        int winner_id = -1;

        void update();
        void render();

      public:
        static Game* instance;

        Game();
        ~Game();
        void start();
        void close();

        SceneManager& get_scene_manager() const;
        const sf::RenderWindow& get_window() const;

        void set_winner(int player_id);
        const int get_winner() const;
    };
}

#endif