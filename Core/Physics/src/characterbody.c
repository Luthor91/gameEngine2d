#include "../include/characterbody.h"

void UpdateCharacterBody(CharacterBody* body, float deltaTime) {
    // Apply velocity to position
    body->transform->bounds->x += body->physics->velocity->x * deltaTime;
    body->transform->bounds->y += body->physics->velocity->y * deltaTime;
    
    // Gravity effect if not grounded
    if (body->physics->isGrounded > 0) {
        body->physics->velocity->y += 9.81f * deltaTime; // Simple gravity effect
    }
}
