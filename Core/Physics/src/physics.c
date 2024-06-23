#include "../include/physics.h"

Physics* Physics_Init(Acceleration* acceleration, ForceManager* force_manager, ImpulseManager* impulse_manager, Velocity* velocity, Material* material) {
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

    physics->forces = (ForceManager*)malloc(sizeof(ForceManager));
    if (physics->forces== NULL) {
        free(physics->acceleration);
        free(physics);
        return NULL;
    }
    physics->forces = force_manager;

    physics->impulses = (ImpulseManager*)malloc(sizeof(ImpulseManager));
    if (physics->impulses== NULL) {
        free(physics->acceleration);
        free(physics);
        return NULL;
    }
    physics->impulses = impulse_manager;

    physics->velocity = (Velocity*)malloc(sizeof(Velocity));
    if (physics->velocity == NULL) {
        free(physics->forces);
        free(physics->acceleration);
        free(physics);
        return NULL;
    }
    physics->velocity = velocity;


    physics->material = (Material*)malloc(sizeof(Material));
    if (physics->material == NULL) {
        free(physics->forces);
        free(physics->acceleration);
        free(physics->velocity);
        free(physics);
        return NULL;
    }
    physics->material = material;
    
    return physics;
}