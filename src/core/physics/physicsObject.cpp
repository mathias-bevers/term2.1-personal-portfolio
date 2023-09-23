#include "physicsObject.h"

namespace personal_portfolio {
    PhysicsObject::PhysicsObject(GameObject* parent) { this->parent = parent; }

    GameObject* PhysicsObject::get_parent() const { return parent; }

    PhysicsObject::~PhysicsObject() = default;
}