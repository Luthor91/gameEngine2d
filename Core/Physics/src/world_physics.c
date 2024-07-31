#include "../include/world_physics.h"
#include <stdlib.h>

WorldPhysics* WorldPhysics_Init(float gravity, float air_density, float global_drag_coefficient) {
    WorldPhysics* world_physics = (WorldPhysics*)malloc(sizeof(WorldPhysics));
    if (!world_physics) return NULL;
    world_physics->gravity = gravity;
    world_physics->air_density = air_density;
    world_physics->global_drag_coefficient = global_drag_coefficient;
    return world_physics;
}

void WorldPhysics_Destroy(WorldPhysics* world_physics) {
    if (world_physics) {
        free(world_physics);
    }
}
