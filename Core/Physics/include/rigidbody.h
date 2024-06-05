#ifndef RIGIDBODY_H
#define RIGIDBODY_H


#include "../../Graphics/include/transform.h"
#include "physics.h"

typedef struct RigidBody {
    Physics physics;
    Transform* transform;
} RigidBody;

typedef struct RigidBodyManager {
    RigidBody* rigidBodies;
    int max_body;
    int index;
} RigidBodyManager;

void UpdateRigidBody(RigidBody* body, float deltaTime);

#endif // RIGIDBODY_H
