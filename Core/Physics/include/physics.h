#ifndef PHYSICS_H
#define PHYSICS_H

#include "core_physics.h"
#include "rigidbody.h"
#include "staticbody.h"
#include "characterbody.h"

typedef struct Physics {
    Acceleration* acceleration;
    Force* force;
    Velocity* velocity;
    MaterialPhysics* material;
    int isGrounded;
} Physics;

Physics* Physics_Init(Acceleration* acceleration, Force* force, Velocity* velocity, MaterialPhysics* material);
void UpdatePhysics(RigidBodyManager* rigidBodies, CharacterBodyManager* characterBodies, StaticBodyManager* staticBodies, float deltaTime);
void ApplyGravity(RigidBody* body, float deltaTime);

#endif // PHYSICS_H
