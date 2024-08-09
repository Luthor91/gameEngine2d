#ifndef WORLD_PHYSICS_H
#define WORLD_PHYSICS_H

#define DEFAULT_WORLDPHYSICS WorldPhysics_Init(9.81f, 1.225f, 0.47f)
/**
 * Représente les propriétés physiques globales du monde.
 */
typedef struct {
    float gravity;               ///< Gravité globale du monde, exprimée en unités de force par unité de masse (m/s²).
    float air_density;           ///< Densité de l'air, utilisée pour calculer la résistance de l'air, exprimée en kg/m³.
    float global_drag_coefficient; ///< Coefficient global de résistance de l'air, utilisé pour modéliser la traînée aérodynamique.
} WorldPhysics;

extern WorldPhysics* WORLD_PHYSICS;
/**
 * Initialise une structure de physique du monde avec les valeurs spécifiées.
 *
 * @param gravity Gravité globale du monde, exprimée en unités de force par unité de masse (m/s²).
 * @param air_density Densité de l'air, exprimée en kg/m³.
 * @param global_drag_coefficient Coefficient global de résistance de l'air.
 * @return Pointeur vers la structure `WorldPhysics` initialisée.
 */
WorldPhysics* WorldPhysics_Init(float gravity, float air_density, float global_drag_coefficient);

/**
 * Détruit une structure de physique du monde, libérant les ressources associées.
 *
 * @param world_physics Pointeur vers la structure `WorldPhysics` à détruire.
 */
void WorldPhysics_Destroy(WorldPhysics* world_physics);

#endif // WORLD_PHYSICS_H
