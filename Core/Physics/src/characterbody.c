#include "../include/characterbody.h"

void UpdateCharacterBody(CharacterBody* body, float deltaTime) {
    // Apply velocity to position
    body->position.x += body->velocity.x * deltaTime;
    body->position.y += body->velocity.y * deltaTime;
    
    // Gravity effect if not grounded
    if (!body->isGrounded) {
        body->velocity.y += 9.81f * deltaTime; // Simple gravity effect
    }
}
