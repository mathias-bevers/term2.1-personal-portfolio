#include "lineCap.h"

namespace personal_portfolio {
    LineCap::LineCap(float radius, float x, float y, GameObject* parent) :
        LineCap::LineCap(radius, sf::Vector2f(x, y), parent)
    {
    }

    LineCap::LineCap(float radius, sf::Vector2f position, GameObject* parent) :
        PhysicsObject(parent), position(position), radius(radius)
    {
    }

    const sf::Vector2f LineCap::get_postion() const
    {
        return parent == nullptr ? position : position + parent->get_position();
    }

    const float LineCap::get_radius() const { return radius; }

    LineCap::~LineCap() = default;
}