#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include <string>

#include "gameObject.h"

namespace personal_portfolio {
    class Button : public GameObject {
      private:
        sf::Text text;
        sf::Font font;
        std::function<void()> on_click;

        bool is_hovering();

      public:
        Button(std::function<void()> callback, std::string text, std::string font_name = std::string());
        ~Button();

        void update() override;
        void render(sf::RenderWindow& window) const override;
    };
}
#endif