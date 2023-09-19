#include "gameScene.h"
#include "../player.h"
#include "../tools/SuperFactory.h"

namespace personal_portfolio {
    SF_Register_Type_Base1(SF_Concrete, GameScene, Scene);
    GameScene::GameScene() : Scene() { }

    void GameScene::start() 
    { 
        Player* player = new Player("test.png");
        game_objects.push_back(player);
    }

    void GameScene::update() {
        Scene::update();
     }

    void GameScene::render(sf::RenderWindow& window) { 
        Scene::render(window);
    }

    GameScene::~GameScene() = default;
}