#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "../../Spatial/include/transform.h"
#include "physics.h"

typedef struct RigidBody {
    Physics* physics;
    Transform* transform;
} RigidBody;

typedef struct RigidBodyManager {
    RigidBody** rigidBodies;
    int max_body;
    int index;
} RigidBodyManager;

RigidBodyManager* RigidBodyManager_Init(int max_body);
RigidBody* RigidBody_Init(Transform* transform, Physics* physics);
void RigidBody_Update(RigidBody* body, float deltaTime);


#endif // RIGIDBODY_H
