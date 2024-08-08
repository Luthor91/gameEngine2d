#include "../include/physics.h"

Physics* Physics_Init(Acceleration* acceleration, ForceManager* force_manager, ImpulseManager* impulse_manager, Velocity* velocity, Material* material) {
    Physics* physics = (Physics*)malloc(sizeof(Physics));
    if (physics == NULL) {
        return NULL;
    }

    physics->acceleration = acceleration ? acceleration : ACCELERATION_ZERO;
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

    physics->velocity = velocity ? velocity : VELOCITY_ZERO;
    if (physics->velocity == NULL) {
        free(physics->impulses);
        free(physics->forces);
        free(physics->acceleration);
        free(physics);
        return NULL;
    }

    physics->material = material ? material : MATERIAL_WOOD;
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
