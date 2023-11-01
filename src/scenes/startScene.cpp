#include "startScene.h"
#include "../core/button.h"
#include "../game.h"
#include "../tools/SuperFactory.h"
#include "../tools/easylogging++.h"
#include "../tools/settings.h"

namespace personal_portfolio {
    SF_Register_Type_Base1(SF_Concrete, StartScene, Scene);
    StartScene::StartScene() : Scene()
    {
        Button* start = new Button(std::bind(&StartScene::load_game, this), "play");
        start->set_position(sf::Vector2f(250, 400));
        game_objects.push_back(start);

        Button* quit = new Button(std::bind(&StartScene::quit_game, this), "quit");
        quit->set_position(sf::Vector2f(250, 600));
        game_objects.push_back(quit);

        if (!font.loadFromFile(PATH_FONTS + "5x5.ttf")) {
            LOG(ERROR) << "Could not load font from file: " << PATH_FONTS + "5x3.ttf";
            exit(1);
        }

        title.setFont(font);
        title.setString("PONG!");
        title.setCharacterSize(150);
        title.setPosition(1000, 100);

        subtitle.setFont(font);
        subtitle.setString("BY: M. Bevers");
        subtitle.setCharacterSize(50);
        subtitle.setPosition(1000, 260);

        Game::instance->set_winner(-1);
    }

    void StartScene::render(sf::RenderWindow& window)
    {
        Scene::render(window);
        window.draw(title);
        window.draw(subtitle);
    }

    void StartScene::load_game() { Game::instance->get_scene_manager().load_scene("GameScene"); }

    void StartScene::quit_game() { Game::instance->close(); }

    StartScene::~StartScene() = default;
}