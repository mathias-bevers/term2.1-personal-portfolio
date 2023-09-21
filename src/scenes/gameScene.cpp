#include <iostream>

#include "../ball.h"
#include "../game.h"
#include "../player.h"
#include "../tools/SuperFactory.h"
#include "../tools/easylogging++.h"
#include "../tools/settings.h"
#include "gameScene.h"

namespace personal_portfolio {
    SF_Register_Type_Base1(SF_Concrete, GameScene, Scene);
    GameScene::GameScene() : Scene()
    {
        game_objects.push_back(new Player(0));
        game_objects.push_back(new Player(1));
        game_objects.push_back(new Ball(std::bind(&GameScene::on_score, this, std::placeholders::_1)));

        std::string font_path = PATH_FONTS + "5x3.ttf";
        if (!font.loadFromFile(font_path)) {
            LOG(ERROR) << "Could not load font with path: " << get_working_dir() << font_path;
        }

        score_datas[0].text.setFont(font);
        score_datas[0].text.setCharacterSize(200);
        score_datas[0].text.setPosition(WINDOW_WIDTH * 0.25, 25);
        score_datas[0].text.setString(std::to_string(score_datas[0].score));

        score_datas[1].text.setFont(font);
        score_datas[1].text.setCharacterSize(200);
        score_datas[1].text.setPosition(WINDOW_WIDTH * 0.75, 25);
        score_datas[1].text.setString(std::to_string(score_datas[1].score));
    }

    void GameScene::update() { Scene::update(); }

    void GameScene::render(sf::RenderWindow& window)
    {
        Scene::render(window);

        for (std::map<int, ScoreData>::iterator it = score_datas.begin(); it != score_datas.end(); ++it) {
            window.draw(it->second.text);
        }
    }

    void GameScene::on_score(int player_id)
    {
        ScoreData& score_data = score_datas[player_id];
        ++score_data.score;
        if (score_data.score == WIN_SCORE) {
            // TODO: go to game over scene.
            LOG(WARNING) << "Win is not yet implemented, closing game";
            Game::instance->close();
            return;
        }

        score_data.text.setString(std::to_string(score_data.score));
    }

    GameScene::~GameScene() = default;
}