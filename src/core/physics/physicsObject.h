#ifndef PHYSICS_H
#define PHYSICS_H

#include "../gameObject.h"

namespace personal_portfolio {
    class PhysicsObject {
      protected:
        const GameObject* parent;

      public:
        PhysicsObject(GameObject* parent);
        virtual ~PhysicsObject();

        // GameObject* get_parent() const;GameObject* get_parent() const;
    };
}
#endif