#include "../include/rigidbody.h"

RigidBodyManager* RigidBodyManager_Init(int max_body) {
    RigidBodyManager* manager = (RigidBodyManager*)malloc(sizeof(RigidBodyManager));

    manager->max_body = max_body;
    manager->index = 0;
    manager->rigidBodies = (RigidBody**)malloc(max_body * sizeof(RigidBody*));

    for (int i = 0; i < max_body; i++) {
        manager->rigidBodies[i] = NULL;
    }

    return manager;
}

RigidBody* RigidBody_Init(Transform* transform, Physics* physics) {
    RigidBody* body = (RigidBody*)malloc(sizeof(RigidBody));

    body->physics = (Physics*)malloc(sizeof(Physics));
    body->transform = (Transform*)malloc(sizeof(Transform));

    body->physics = physics;
    body->transform = transform;

    return body;
}

void RigidBody_Update(RigidBody* body, float deltaTime) {
    // Calculer les nouvelles vitesses en fonction de l'accélération
    body->physics->velocity->x += body->physics->acceleration->x * deltaTime;
    body->physics->velocity->y += body->physics->acceleration->y * deltaTime;

    // Calculer les nouvelles positions en fonction des vitesses et de l'accélération
    body->transform->position->x += body->physics->velocity->x * deltaTime + 0.5f * body->physics->acceleration->x * deltaTime * deltaTime;
    body->transform->position->y += body->physics->velocity->y * deltaTime + 0.5f * body->physics->acceleration->y * deltaTime * deltaTime;
}

