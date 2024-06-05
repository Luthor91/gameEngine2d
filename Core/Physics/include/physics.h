#ifndef PHYSICS_H
#define PHYSICS_H

#include "rigidbody.h"
#include "characterbody.h"
#include "staticbody.h"
#include "collision.h"
#include "material_physics.h"

typedef struct Physics {
    Acceleration* acceleration;
    Force* force;
    Velocity* velocity;
    MaterialPhysics* material;
} Physics;

typedef struct Acceleration {
    float x, y;
} Acceleration;

typedef struct Force {
    float x, y;
} Force;

typedef struct Velocity {
    float x, y;
} Velocity;

void UpdatePhysics(RigidBodyManager* rigidBodies, CharacterBodyManager* characterBodies, StaticBodyManager* staticBodies, float deltaTime);
void ApplyGravity(RigidBody* body, float deltaTime);

#endif // PHYSICS_H
