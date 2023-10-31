#include "startScene.h"
#include "../core/button.h"
#include "../game.h"
#include "../tools/SuperFactory.h"

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
    }

    void StartScene::render(sf::RenderWindow& window) { Scene::render(window); }

    void StartScene::load_game() { Game::instance->get_scene_manager().load_scene("GameScene"); }

    void StartScene::quit_game() { Game::instance->close(); }

    StartScene::~StartScene() = default;
}