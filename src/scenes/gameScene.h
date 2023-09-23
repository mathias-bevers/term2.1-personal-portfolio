#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <map>

#include "../core/scene.h"
#include "../core/physics/physicsObject.h"

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
        const std::vector<PhysicsObject*>& get_physics_objects() const;

      private:
        std::vector<PhysicsObject*> physics_objects;
        std::map<int, ScoreData> score_datas = {{0, ScoreData()}, {1, ScoreData()}};
        sf::Font font;

        void on_score(const int player_id);
    };
}
#endif