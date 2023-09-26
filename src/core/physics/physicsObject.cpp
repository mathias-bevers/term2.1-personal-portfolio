#include "physicsObject.h"

namespace personal_portfolio {
    PhysicsObject::PhysicsObject(const GameObject* parent) : parent(parent) { }

    const GameObject* PhysicsObject::get_parent() const { return parent; }

    PhysicsObject::~PhysicsObject() = default;
}