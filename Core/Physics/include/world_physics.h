// world_physics.h

#ifndef WORLD_PHYSICS_H
#define WORLD_PHYSICS_H

typedef struct {
    float gravity;            // Gravité globale du monde
    float air_density;        // Densité de l'air pour la résistance
    float global_drag_coefficient; // Coefficient global de résistance de l'air
} WorldPhysics;

WorldPhysics* WorldPhysics_Init(float gravity, float air_density, float global_drag_coefficient);
void WorldPhysics_Destroy(WorldPhysics* world_physics);

#endif // WORLD_PHYSICS_H
