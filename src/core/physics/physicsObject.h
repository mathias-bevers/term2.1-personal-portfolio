#ifndef PHYSICS_H
#define PHYSICS_H

#include "../gameObject.h"

namespace personal_portfolio {
    class PhysicsObject {
      protected:
        const GameObject* parent;

      public:
        PhysicsObject(const GameObject* parent = nullptr);
        virtual ~PhysicsObject();

        const GameObject* get_parent() const;
    };
}
#endif