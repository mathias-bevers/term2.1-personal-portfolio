#ifndef LINECAP_H
#define LINECAP_H

#include <SFML/System/Vector2.hpp>
#include "physicsObject.h"

namespace personal_portfolio {
    class LineCap : public PhysicsObject {
        private:
            const sf::Vector2f position;
            const float radius;

            public:
            LineCap(float radius, float x, float y, GameObject* parent = nullptr);
            LineCap(float radius, sf::Vector2f position, GameObject* parent = nullptr);

            const sf::Vector2f get_postion() const;
            const float get_radius() const;

            ~LineCap();
    };
}
#endif