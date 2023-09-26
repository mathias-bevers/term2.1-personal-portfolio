#include "physicsObject.h"

namespace personal_portfolio {
    PhysicsObject::PhysicsObject(const GameObject* parent) : parent(parent) { }
    
    PhysicsObject::~PhysicsObject() = default;
}