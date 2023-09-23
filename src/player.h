#ifndef PLAYER_H
#define PLAYER_H

#include "core/gameObject.h"
#include "scenes/gameScene.h"

namespace personal_portfolio {
    class Player : public GameObject {
      public:
        Player(int id);
        ~Player();

        void update() override;
        const std::vector<PhysicsObject*>& get_physics_objects() const;

      private:
        std::vector<PhysicsObject*> physics_objects;
        const int id;
        sf::Keyboard::Key up;
        sf::Keyboard::Key down;
        const float move_speed = 0.35f;

        void move(const sf::Vector2f velocity);
    };
}
#endif