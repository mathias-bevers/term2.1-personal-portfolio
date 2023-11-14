#ifndef HIT_H
#define HIT_H

#include <SFML/System/Vector2.hpp>

#include "physicsObject.h"

namespace personal_portfolio {
    class Hit {
      private:
        sf::Vector2f normal;
        PhysicsObject& other;
        float toi;

      public:
        Hit(sf::Vector2f normal, PhysicsObject& other, float toi);
        ~Hit();

        const sf::Vector2f get_normal() const;
        PhysicsObject& get_other() const;
        const float get_toi() const;
    };
}
#endif