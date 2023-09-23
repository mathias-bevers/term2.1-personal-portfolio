#include "hit.h"

namespace personal_portfolio {
    Hit::Hit(sf::Vector2f normal, PhysicsObject& other, float toi) : other(other)
    {
        this->normal = normal;
        this->toi = toi;
    }

    const sf::Vector2f Hit::get_normal() const { return normal; }

    PhysicsObject& Hit::get_other() const { return other; }

    const float Hit::get_toi() const { return toi; }

    Hit::~Hit() = default;
}