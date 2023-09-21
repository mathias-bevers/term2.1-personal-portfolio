#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../core/scene.h"

namespace personal_portfolio {
    class GameScene : public Scene {
      public:
        GameScene();
        ~GameScene();

        void start() override;
        void update() override;
        void render(sf::RenderWindow& window) override;
    };
}
#endif