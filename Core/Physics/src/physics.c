#include "../include/physics.h"

Physics* Physics_Init(Acceleration* acceleration, Force* force, Velocity* velocity, MaterialPhysics* material) {
    Physics* physics = (Physics*)malloc(sizeof(Physics));
    if (physics == NULL) {
        return NULL;
    }

    physics->acceleration = (Acceleration*)malloc(sizeof(Acceleration));
    if (physics->acceleration == NULL) {
        free(physics);
        return NULL;
    }
    physics->acceleration = acceleration;

    physics->force = (Force*)malloc(sizeof(Force));
    if (physics->force == NULL) {
        free(physics->acceleration);
        free(physics);
        return NULL;
    }
    physics->force = force;

    physics->velocity = (Velocity*)malloc(sizeof(Velocity));
    if (physics->velocity == NULL) {
        free(physics->force);
        free(physics->acceleration);
        free(physics);
        return NULL;
    }
    physics->velocity = velocity;


    physics->material = (MaterialPhysics*)malloc(sizeof(MaterialPhysics));
    if (physics->material == NULL) {
        free(physics->force);
        free(physics->acceleration);
        free(physics->velocity);
        free(physics);
        return NULL;
    }
    physics->material = material;
    
    return physics;
}

void UpdatePhysics(RigidBodyManager* rigidBodies, CharacterBodyManager* characterBodies, StaticBodyManager* staticBodies, float deltaTime) {
    // Update all rigid bodies
    for (int i = 0; i < rigidBodies->max_body; i++) {
        ApplyGravity(&rigidBodies[i], deltaTime);
        UpdateRigidBody(&rigidBodies[i], deltaTime);
        
        // Check collisions with static bodies
        for (int j = 0; j < staticBodies->max_body; j++) {
            HandleCollision(&rigidBodies[i], &staticBodies[j]);
        }
    }

    // Update all character bodies
    for (int i = 0; i < characterBodies->max_body; i++) {
        UpdateCharacterBody(&characterBodies[i], deltaTime);
        
        // Check collisions with static bodies
        for (int j = 0; j < staticBodies->max_body; j++) {
            // HandleCharacterCollision(&characterBodies[i], &staticBodies[j]); // Implement as needed
        }
    }
}

void ApplyGravity(RigidBody* body, float deltaTime) {
    body->physics->acceleration->y += 9.81f * deltaTime; // Gravity effect
}
