#include "../include/collision.h"
#include <math.h>

int CheckCollision(Vector2 posA, Vector2 posB, float radiusA, float radiusB) {
    float distX = posA.x - posB.x;
    float distY = posA.y - posB.y;
    float distance = sqrt(distX * distX + distY * distY);

    return distance < (radiusA + radiusB);
}

void HandleCollision(RigidBody* body, StaticBody* staticBody) {
    if (CheckCollision(body->position, staticBody->position, 1.0f, 1.0f)) {
        body->velocity.x = 0;
        body->velocity.y = 0;
    }
}
