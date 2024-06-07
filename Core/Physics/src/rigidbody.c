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
    // Vérifier si body->physics est NULL
    if (body->physics == NULL) {
        // Ne rien faire si body->physics est NULL
        return;
    }

    // Définir des valeurs par défaut pour les propriétés matérielles
    float default_mass = 1.0f;
    float mass = (body->physics->material != NULL && body->physics->material->mass != 0.0f) ? body->physics->material->mass : default_mass;

    // Calculer la force nette à partir des forces appliquées
    Force* netForce = ForceManager_CalculateNetForce(body->physics->forces);

    // Calculer l'accélération en fonction de la force et de la masse
    body->physics->acceleration->x = netForce->magnitude * cos(netForce->direction) / mass;
    body->physics->acceleration->y = netForce->magnitude * sin(netForce->direction) / mass;

    // Mettre à jour la vitesse en fonction de l'accélération
    body->physics->velocity->x += body->physics->acceleration->x * deltaTime;
    body->physics->velocity->y += body->physics->acceleration->y * deltaTime;

    // Mettre à jour la position en fonction de la vitesse et de l'accélération
    body->transform->position->x += body->physics->velocity->x * deltaTime + 0.5f * body->physics->acceleration->x * deltaTime * deltaTime;
    body->transform->position->y += body->physics->velocity->y * deltaTime + 0.5f * body->physics->acceleration->y * deltaTime * deltaTime;

    // Libérer la mémoire allouée pour netForce
    free(netForce);
}
