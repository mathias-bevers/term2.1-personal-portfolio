#ifndef ENDSCENE_H
#define ENDSCENE_H

#include "../core/scene.h"

namespace personal_portfolio {
    class EndScene : public Scene {
      public:
        EndScene();
        ~EndScene();

        void render(sf::RenderWindow& window) override;

      private:
        sf::Font font;
        sf::Text title;
        
        void continue_to_menu();
    };
}
#endif