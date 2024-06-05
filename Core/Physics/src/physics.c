#include "../include/physics.h"

void UpdatePhysics(RigidBody* rigidBodies, int numRigidBodies, CharacterBody* characterBodies, int numCharacterBodies, StaticBody* staticBodies, int numStaticBodies, float deltaTime) {
    // Update all rigid bodies
    for (int i = 0; i < numRigidBodies; i++) {
        ApplyGravity(&rigidBodies[i], deltaTime);
        UpdateRigidBody(&rigidBodies[i], deltaTime);
        
        // Check collisions with static bodies
        for (int j = 0; j < numStaticBodies; j++) {
            HandleCollision(&rigidBodies[i], &staticBodies[j]);
        }
    }

    // Update all character bodies
    for (int i = 0; i < numCharacterBodies; i++) {
        UpdateCharacterBody(&characterBodies[i], deltaTime);
        
        // Check collisions with static bodies
        for (int j = 0; j < numStaticBodies; j++) {
            // HandleCharacterCollision(&characterBodies[i], &staticBodies[j]); // Implement as needed
        }
    }
}

void ApplyGravity(RigidBody* body, float deltaTime) {
    body->acceleration.y += 9.81f * deltaTime; // Gravity effect
}
