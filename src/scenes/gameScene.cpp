#include <iostream>

#include "../ball.h"
#include "../player.h"
#include "../tools/SuperFactory.h"
#include "gameScene.h"

namespace personal_portfolio {
    SF_Register_Type_Base1(SF_Concrete, GameScene, Scene);
    GameScene::GameScene() : Scene() { }

    void GameScene::start()
    {
        game_objects.push_back(new Player(0));
        game_objects.push_back(new Player(1));
        game_objects.push_back(new Ball(std::bind(&GameScene::on_score, this, std::placeholders::_1)));
    }

    void GameScene::update() { Scene::update(); }

    void GameScene::render(sf::RenderWindow& window) { Scene::render(window); }

    void GameScene::on_score(int player_id)
    {
        std::cout << "player " << player_id << " scored!" << std::endl;
    }

    GameScene::~GameScene() = default;
}