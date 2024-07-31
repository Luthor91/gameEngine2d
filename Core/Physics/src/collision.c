#include "../include/collision.h"
#include <math.h>

int Collision_Check(Point2D* posA, Point2D* posB, float radiusA, float radiusB) {
    float distX = posA->x - posB->x;
    float distY = posA->y - posB->y;
    float distance = sqrt(distX * distX + distY * distY);

    return distance < (radiusA + radiusB);
}

void Collision_Handle(RigidBody* body, StaticBody* staticBody) {
    if (Collision_Check(body->transform->position, staticBody->transform->position, 1.0f, 1.0f)) {
        body->physics->velocity->x = 0;
        body->physics->velocity->y = 0;
    }
}
