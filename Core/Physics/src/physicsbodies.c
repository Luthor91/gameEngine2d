#include "../include/physicsbodies.h"

PhysicsBodies* PHYSICSBODIES_MANAGER = NULL;

PhysicsBodies* PhysicBodies_Init(CharacterBodyManager* cb_manager, RigidBodyManager* rb_manager, StaticBodyManager* sb_manager) {
    PhysicsBodies* physics_bodies = (PhysicsBodies*)malloc(sizeof(PhysicsBodies));
    if (physics_bodies == NULL) {
        return NULL;
    }

    physics_bodies->cb_manager = cb_manager;
    physics_bodies->rb_manager = rb_manager;
    physics_bodies->sb_manager = sb_manager; 

    return physics_bodies;
}

void PhysicBodies_Update(PhysicsBodies* physics_bodies, float deltaTime) {

    if (physics_bodies->rb_manager && physics_bodies->rb_manager->index > 0) {
        for (int i = 0; i < physics_bodies->rb_manager->max_body ; i++) {
            if (physics_bodies->rb_manager->bodies[i]) {
                Body_Update(
                    physics_bodies->rb_manager->bodies[i]->physics,
                    physics_bodies->rb_manager->bodies[i]->transform,
                    physics_bodies->rb_manager->bodies[i]->hitbox, 
                    deltaTime);
            }
        }
    }

    if (physics_bodies->cb_manager && physics_bodies->cb_manager->index > 0) {
        for (int i = 0; i < physics_bodies->cb_manager->max_body ; i++) {
            if (physics_bodies->cb_manager->bodies[i]) {
                Body_Update(
                    physics_bodies->cb_manager->bodies[i]->physics,
                    physics_bodies->cb_manager->bodies[i]->transform,
                    physics_bodies->cb_manager->bodies[i]->hitbox, 
                    deltaTime);
            }
        }
    } 
}

void Body_Update(Physics* physics, Transform* transform, Hitbox* hitbox, float deltaTime) {
    // Vérifier si physics est NULL
    if (physics == NULL) {
        return;
    }

    // Définir la masse avec une valeur par défaut si nécessaire
    float mass = (physics->material != NULL && physics->material->mass != 0.0f) ? physics->material->mass : 1.0f;

    // Calculer la force nette à partir des forces appliquées
    Force* netForce = ForceManager_CalculateNetForce(physics->forces);

    if (netForce == NULL) {
        return; // Vérifier si netForce n'est pas NULL
    }

    // Calculer les composantes de la force nette
    float netForceX = netForce->magnitude * cos(netForce->direction);
    float netForceY = netForce->magnitude * sin(netForce->direction);

    // Libérer la mémoire allouée pour netForce
    free(netForce);

    // Appliquer les impulsions si présentes et ajouter leurs composantes à la force nette
    for (int i = 0; i < physics->impulses->index; i++) {
        Impulse* impulse = physics->impulses->impulses[i];
        
        // Appliquer l'impulsion si elle est toujours active
        if (impulse->timeElapsed < impulse->duration) {
            float impulseX = impulse->magnitude * cos(impulse->direction);
            float impulseY = impulse->magnitude * sin(impulse->direction);

            // Appliquer l'impulsion instantanément à la vitesse
            physics->velocity->x += (impulseX / mass) * (deltaTime / impulse->duration);
            physics->velocity->y += (impulseY / mass) * (deltaTime / impulse->duration);

            // Mettre à jour le temps écoulé
            impulse->timeElapsed += deltaTime;

            // Si l'impulsion est terminée, la détruire
            if (impulse->timeElapsed >= impulse->duration) {
                Impulse_Destroy(impulse);
                physics->impulses->impulses[i] = NULL;
            }
        }
    }

    // Supprimer les impulsions terminées de la liste
    int newIndex = 0;
    for (int i = 0; i < physics->impulses->index; i++) {
        if (physics->impulses->impulses[i] != NULL) {
            physics->impulses->impulses[newIndex++] = physics->impulses->impulses[i];
        }
    }
    physics->impulses->index = newIndex;

    // Calculer l'accélération en fonction de la force nette et de la masse
    physics->acceleration->x = netForceX / mass;
    physics->acceleration->y = netForceY / mass;

    // Mettre à jour la vitesse en fonction de l'accélération
    physics->velocity->x += physics->acceleration->x * deltaTime;
    physics->velocity->y += physics->acceleration->y * deltaTime;

    // Mettre à jour la position en fonction de la vitesse et de l'accélération
    transform->position->x += physics->velocity->x * deltaTime + 0.5f * physics->acceleration->x * deltaTime * deltaTime;
    transform->position->y += physics->velocity->y * deltaTime + 0.5f * physics->acceleration->y * deltaTime * deltaTime;

    hitbox->transform->position = transform->position;
}