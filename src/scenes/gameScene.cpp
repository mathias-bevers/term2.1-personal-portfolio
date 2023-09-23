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
        for (int i = 0; i < 2; ++i) {
            Player* player = new Player(i);
            
            const std::vector<PhysicsObject*>& to_add = player->get_physics_objects();
            physics_objects.reserve(physics_objects.size() + to_add.size());
            physics_objects.insert(physics_objects.end(), to_add.begin(), to_add.end());

            game_objects.push_back(player);
        }

        game_objects.push_back(new Ball(std::bind(&GameScene::on_score, this, std::placeholders::_1), *this));

        std::string font_path = PATH_FONTS + "5x3.ttf";
        if (!font.loadFromFile(font_path)) {
            LOG(ERROR) << "Could not load font with path: " << get_working_dir() << font_path;
        }

        for (std::map<int, ScoreData>::iterator it = score_datas.begin(); it != score_datas.end(); ++it) {
            sf::Text& text = it->second.text;
            text.setFont(font);
            text.setCharacterSize(200);
            text.setString(std::to_string(it->second.score));
        }

        score_datas[0].text.setPosition(WINDOW_WIDTH * 0.25, 25);
        score_datas[1].text.setPosition(WINDOW_WIDTH * 0.75, 25);
    }

    const std::vector<PhysicsObject*>& GameScene::get_physics_objects() const { return physics_objects; }

    void GameScene::update() { Scene::update(); }

    void GameScene::render(sf::RenderWindow& window)
    {
        Scene::render(window);

        for (std::map<int, ScoreData>::iterator it = score_datas.begin(); it != score_datas.end(); ++it) {
            window.draw(it->second.text);
        }
    }

    void GameScene::on_score(const int player_id)
    {
        ScoreData& score_data = score_datas[player_id];
        ++score_data.score;
        if (score_data.score == WIN_SCORE) {
            // TODO: go to game over scene.
            LOG(INFO) << player_id + 1 << " has won!";
            LOG(WARNING) << "Win is not yet implemented, closing game";
            Game::instance->close();
            return;
        }

        score_data.text.setString(std::to_string(score_data.score));
    }

    GameScene::~GameScene() = default;
}