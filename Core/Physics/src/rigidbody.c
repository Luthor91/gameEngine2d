#include "../include/rigidbody.h"

void UpdateRigidBody(RigidBody* body, float deltaTime) {
    // Apply acceleration to velocity
    body->velocity.x += body->acceleration.x * deltaTime;
    body->velocity.y += body->acceleration.y * deltaTime;
    
    // Apply velocity to position
    body->position.x += body->velocity.x * deltaTime;
    body->position.y += body->velocity.y * deltaTime;
    
    // Reset acceleration
    body->acceleration.x = 0;
    body->acceleration.y = 0;
}
