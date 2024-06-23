#ifndef COLLISION_H
#define COLLISION_H

#include "physics.h"
#include "rigidbody.h"
#include "staticbody.h"
#include "../../Spatial/include/point2d.h"

int CheckCollision(Point2D* posA, Point2D* posB, float radiusA, float radiusB);
void HandleCollision(RigidBody* body, StaticBody* staticBody);

#endif // COLLISION_H
