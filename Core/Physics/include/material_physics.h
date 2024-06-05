// material_physics.h

#ifndef MATERIAL_PHYSICS_H
#define MATERIAL_PHYSICS_H

typedef struct MaterialPhysics {
    float friction_coefficient;  // Coefficient de friction du matériau
    float restitution_coefficient; // Coefficient de restitution pour les collisions
    float density;               // Densité du matériau
    float mass;
    float friction;
    float restitution;  // bounce
} MaterialPhysics;

MaterialPhysics* MaterialPhysics_Init(float friction, float restitution, float density);
void MaterialPhysics_Destroy(MaterialPhysics* material_physics);

#endif // MATERIAL_PHYSICS_H
