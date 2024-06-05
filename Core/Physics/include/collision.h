#ifndef COLLISION_H
#define COLLISION_H

#include "physics.h"
#include "rigidbody.h"
#include "staticbody.h"

int CheckCollision(Vector2 posA, Vector2 posB, float radiusA, float radiusB);
void HandleCollision(RigidBody* body, StaticBody* staticBody);

#endif // COLLISION_H
