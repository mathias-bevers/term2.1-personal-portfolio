#include <sstream>

#include "endScene.h"

#include "../core/button.h"
#include "../game.h"
#include "../tools/SuperFactory.h"
#include "../tools/easylogging++.h"
#include "../tools/settings.h"

namespace personal_portfolio {
    SF_Register_Type_Base1(SF_Concrete, EndScene, Scene);

    EndScene::EndScene() : Scene()
    {
        Button* continue_button = new Button(std::bind(&EndScene::continue_to_menu, this), "continue");
        continue_button->set_position(sf::Vector2f(800, 800));
        game_objects.push_back(continue_button);

        if (!font.loadFromFile(PATH_FONTS + "5x5.ttf")) {
            LOG(ERROR) << "Could not load font from file: " << PATH_FONTS + "5x3.ttf";
            exit(1);
        }

        title.setFont(font);
        title.setCharacterSize(100);

        std::stringstream ss;
        ss << "Player " << Game::instance->get_winner() + 1 << " has won!";
        title.setString(ss.str());

        sf::FloatRect title_rect = title.getGlobalBounds();
        title.setOrigin(title_rect.left + title_rect.width / 2.0f, 0);
        title.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, 25.0f));
    }

    void EndScene::render(sf::RenderWindow& window)
    {
        Scene::render(window);
        window.draw(title);
    }

    void EndScene::continue_to_menu() { Game::instance->get_scene_manager().load_scene("StartScene"); }

    EndScene::~EndScene() = default;
}