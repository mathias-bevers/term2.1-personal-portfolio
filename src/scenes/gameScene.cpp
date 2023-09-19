#include "gameScene.h"
#include "../player.h"
#include "../ball.h"
#include "../tools/SuperFactory.h"

namespace personal_portfolio {
    SF_Register_Type_Base1(SF_Concrete, GameScene, Scene);
    GameScene::GameScene() : Scene() { }

    void GameScene::start()
    {
        game_objects.push_back(new Player(0));
        game_objects.push_back(new Player(1));
        game_objects.push_back(new Ball());
    }

    void GameScene::update() { Scene::update(); }

    void GameScene::render(sf::RenderWindow& window) { Scene::render(window); }

    GameScene::~GameScene() = default;
}