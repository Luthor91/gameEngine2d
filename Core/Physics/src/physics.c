#include "../include/physics.h"

Physics* Physics_Init(Acceleration* acceleration, Force* force, Velocity* velocity, Material* material) {
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


    physics->material = (Material*)malloc(sizeof(Material));
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