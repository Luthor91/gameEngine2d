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
        return;
    }

    // Définir la masse avec une valeur par défaut si nécessaire
    float mass = (body->physics->material != NULL && body->physics->material->mass != 0.0f) ? body->physics->material->mass : 1.0f;

    // Calculer la force nette à partir des forces appliquées
    Force* netForce = ForceManager_CalculateNetForce(body->physics->forces);

    if (netForce == NULL) {
        return; // Vérifier si netForce n'est pas NULL
    }

    // Calculer les composantes de la force nette
    float netForceX = netForce->magnitude * cos(netForce->direction);
    float netForceY = netForce->magnitude * sin(netForce->direction);

    // Libérer la mémoire allouée pour netForce
    free(netForce);

    // Appliquer les impulsions si présentes et ajouter leurs composantes à la force nette
    for (int i = 0; i < body->physics->impulses->index; i++) {
        Impulse* impulse = body->physics->impulses->impulses[i];
        
        // Appliquer l'impulsion si elle est toujours active
        if (impulse->timeElapsed < impulse->duration) {
            float impulseX = impulse->magnitude * cos(impulse->direction);
            float impulseY = impulse->magnitude * sin(impulse->direction);

            // Appliquer l'impulsion instantanément à la vitesse
            body->physics->velocity->x += (impulseX / mass) * (deltaTime / impulse->duration);
            body->physics->velocity->y += (impulseY / mass) * (deltaTime / impulse->duration);

            // Mettre à jour le temps écoulé
            impulse->timeElapsed += deltaTime;

            // Si l'impulsion est terminée, la détruire
            if (impulse->timeElapsed >= impulse->duration) {
                Impulse_Destroy(impulse);
                body->physics->impulses->impulses[i] = NULL;
            }
        }
    }

    // Supprimer les impulsions terminées de la liste
    int newIndex = 0;
    for (int i = 0; i < body->physics->impulses->index; i++) {
        if (body->physics->impulses->impulses[i] != NULL) {
            body->physics->impulses->impulses[newIndex++] = body->physics->impulses->impulses[i];
        }
    }
    body->physics->impulses->index = newIndex;

    // Calculer l'accélération en fonction de la force nette et de la masse
    body->physics->acceleration->x = netForceX / mass;
    body->physics->acceleration->y = netForceY / mass;

    // Mettre à jour la vitesse en fonction de l'accélération
    body->physics->velocity->x += body->physics->acceleration->x * deltaTime;
    body->physics->velocity->y += body->physics->acceleration->y * deltaTime;

    // Mettre à jour la position en fonction de la vitesse et de l'accélération
    body->transform->position->x += body->physics->velocity->x * deltaTime + 0.5f * body->physics->acceleration->x * deltaTime * deltaTime;
    body->transform->position->y += body->physics->velocity->y * deltaTime + 0.5f * body->physics->acceleration->y * deltaTime * deltaTime;
}

