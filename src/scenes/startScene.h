#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "../core/scene.h"

namespace personal_portfolio {
    class StartScene : public Scene {
      public:
        StartScene();
        ~StartScene();

        void render(sf::RenderWindow& window) override;

      private:
        sf::Font font;
        sf::Text title;
        sf::Text subtitle;

        void load_game();
        void quit_game();
    };
}
#endif