#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../core/scene.h"
#include <stdio.h>

namespace personal_portfolio {
    class GameScene : public Scene {
      public:
        GameScene();
        ~GameScene();

        void start() override;
        void update() override;
        void render(sf::RenderWindow& window) override;

        private:
        void on_score(int player_id);
    };
}
#endif