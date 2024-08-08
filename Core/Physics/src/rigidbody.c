#include "../include/rigidbody.h"

RigidBodyManager* RigidBodyManager_Init(int max_body) {
    RigidBodyManager* manager = (RigidBodyManager*)malloc(sizeof(RigidBodyManager));

    manager->max_body = max_body;
    manager->index = 0;
    manager->bodies = (RigidBody**)malloc(max_body * sizeof(RigidBody*));

    for (int i = 0; i < max_body; i++) {
        manager->bodies[i] = NULL;
    }

    return manager;
}

RigidBody* RigidBody_Init(Transform* transform, Physics* physics) {
    RigidBody* body = (RigidBody*)malloc(sizeof(RigidBody));
    body->physics = (Physics*)malloc(sizeof(Physics));
    body->transform = (Transform*)malloc(sizeof(Transform));

    if (transform == NULL) {
        transform = Transform_Init(NULL, NULL, NULL, 0, 0);
    }

    if (physics == NULL) {
        physics = Physics_Init(NULL, NULL, NULL, NULL, NULL);
    }

    body->physics = physics;
    body->transform = transform;

    return body;
}

void RigidBodyManager_Add(RigidBodyManager* manager, ...) {
    va_list args;
    va_start(args, manager);

    int num_bodies = 0;
    RigidBody* body;

    // Compter les arguments variadiques jusqu'à rencontrer NULL
    while ((body = va_arg(args, RigidBody*)) != NULL) {
        num_bodies++;
    }
    va_end(args);
    va_start(args, manager); // Réinitialiser va_list pour réutilisation

    for (int i = 0; i < num_bodies; i++) {
        
        body = va_arg(args, RigidBody*);

        if (body == NULL) {
            fprintf(stderr, "RigidBodyManager_AddBodies: RigidBody at index %d is NULL\n", i);
            break;
        }

        if (manager->index >= manager->max_body) {
            fprintf(stderr, "RigidBodyManager_AddBodies: Maximum number of rigid bodies reached\n");
            break;
        }

        manager->bodies[manager->index++] = body;
    }

    va_end(args);
}

void RigidBodyManager_Update(RigidBodyManager* manager, float deltaTime) {
    for (int i = 0; i < manager->max_body ; i++) {
        if (manager->bodies[i]) {
            RigidBody_Update(manager->bodies[i], deltaTime);
        }
    }
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
