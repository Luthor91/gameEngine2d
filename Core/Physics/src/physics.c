#include "../include/physics.h"

Physics* Physics_Init(Acceleration* acceleration, ForceManager* force_manager, ImpulseManager* impulse_manager, Velocity* velocity, Material* material) {
    Physics* physics = (Physics*)malloc(sizeof(Physics));
    if (physics == NULL) {
        return NULL;
    }

    physics->acceleration = acceleration ? acceleration : Acceleration_Init(NULL);
    if (physics->acceleration == NULL) {
        free(physics);
        return NULL;
    }

    physics->forces = force_manager ? force_manager : ForceManager_Init(DEFAULT_MAX_FORCES);
    if (physics->forces == NULL) {
        free(physics->acceleration);
        free(physics);
        return NULL;
    }

    physics->impulses = impulse_manager ? impulse_manager : ImpulseManager_Init(DEFAULT_MAX_IMPULSES);
    if (physics->impulses == NULL) {
        free(physics->forces);
        free(physics->acceleration);
        free(physics);
        return NULL;
    }

    physics->velocity = velocity ? velocity : Velocity_Init(0, 0);
    if (physics->velocity == NULL) {
        free(physics->impulses);
        free(physics->forces);
        free(physics->acceleration);
        free(physics);
        return NULL;
    }

    physics->material = material ? material : Material_Init(0.5f, 0.5f, 1.0f, 1.0f, 0.5f, 0.5f);
    if (physics->material == NULL) {
        free(physics->velocity);
        free(physics->impulses);
        free(physics->forces);
        free(physics->acceleration);
        free(physics);
        return NULL;
    }

    return physics;
}
