#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../core/scene.h"
#include <map>

namespace personal_portfolio {
    struct ScoreData {
        int score;
        sf::Text text;
    };

    class GameScene : public Scene {
      public:
        GameScene();
        ~GameScene();

        void update() override;
        void render(sf::RenderWindow& window) override;

      private:
        std::map<int, ScoreData> score_datas = {{0, ScoreData()}, {1, ScoreData()}};
        sf::Font font;

        void on_score(int player_id);
    };
}
#endif