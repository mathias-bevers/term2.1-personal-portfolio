#include <iostream>

#include "../ball.h"
#include "../core/physics/line.h"
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
        game_objects.push_back(new Ball(std::bind(&GameScene::on_score, this, std::placeholders::_1), *this));
        for (int i = 0; i < 2; ++i) {
            Player* player = new Player(i);

            physics_objects.reserve(physics_objects.size() + player->get_physics_objects().size());
            physics_objects.insert(physics_objects.end(), player->get_physics_objects().begin(),
                                   player->get_physics_objects().end());

            game_objects.push_back(player);
        }

        physics_objects.push_back(new Line(-10, 0, WINDOW_WIDTH + 10, 0));
        physics_objects.push_back(new Line(WINDOW_WIDTH + 10, WINDOW_HIGHT, -10, WINDOW_HIGHT));

        // ---------------------------------------------------------- LOADING FONT
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

    const std::vector<PhysicsObject*>& GameScene::get_physics_objects() { return physics_objects; }

    void GameScene::update() { Scene::update(); }

    void GameScene::render(sf::RenderWindow& window)
    {
        Scene::render(window);

        for (std::map<int, ScoreData>::iterator it = score_datas.begin(); it != score_datas.end(); ++it) {
            window.draw(it->second.text);
        }

        if (!DEBUG) {
            return;
        }

        for (std::vector<PhysicsObject*>::iterator it = physics_objects.begin(); it != physics_objects.end();
             ++it) {
            if (Line* line = dynamic_cast<Line*>(*it)) {
                line->render(window);
            }
        }
    }

    void GameScene::on_score(const int player_id)
    {
        ScoreData& score_data = score_datas[player_id];
        ++score_data.score;
        if (score_data.score == WIN_SCORE) {
            // TODO: go to game over scene.g
            LOG(INFO) << player_id + 1 << " has won!";
            LOG(WARNING) << "Win is not yet implemented, closing game";
            Game::instance->close();
            return;
        }

        score_data.text.setString(std::to_string(score_data.score));
    }

    GameScene::~GameScene() = default;
}