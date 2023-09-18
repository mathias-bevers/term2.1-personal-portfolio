#include "gameScene.h"
#include "../player.h"

namespace personal_portfolio {
    GameScene::GameScene() : Scene("game") { game_objects.push_back(new Player("test.png")); }

    void GameScene::update() { }

    void GameScene::render(sf::RenderWindow& window) { }

    GameScene::~GameScene() = default;
}