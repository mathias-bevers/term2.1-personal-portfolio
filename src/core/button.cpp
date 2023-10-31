#include "button.h"
#include "../game.h"
#include "../tools/settings.h"

namespace personal_portfolio {
    Button::Button(std::function<void()> callback, std::string text, std::string font_name) :
        GameObject("button.png")
    {
        font_name = PATH_FONTS + (font_name.empty() ? "5x3.ttf" : font_name);
        if (!font.loadFromFile(font_name)) {
            exit(1);
        }
        on_click = callback;
        this->text.setFont(font);
        this->text.setCharacterSize(30);
        this->text.setString(text);
    }

    void Button::render(sf::RenderWindow& window) const
    {
        GameObject::render(window);
        window.draw(text);
    }

    void Button::update()
    {
        GameObject::update();
        text.setPosition(get_position() - (get_size() * 0.45f));

        if (!is_hovering()) {
            set_color(sf::Color(155, 155, 155));
            return;
        }

        set_color(sf::Color::White);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            on_click();
        }
    }

    bool Button::is_hovering()
    {
        const sf::RenderWindow& window = Game::instance->get_window();
        const sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        const sf::Vector2f min = get_position() - (get_size() * 0.5f);
        const sf::Vector2f max = get_position() + (get_size() * 0.5f);

        if (mouse_position.x < min.x || mouse_position.x > max.x) {
            return false;
        }
        if (mouse_position.y < min.y || mouse_position.y > max.y) {
            return false;
        }

        return true;
    }

    Button::~Button() = default;
}