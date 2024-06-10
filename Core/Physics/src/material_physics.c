#include "../include/material_physics.h"
#include <stdlib.h>

MaterialPhysics* MaterialPhysics_Init(float friction, float restitution, float density) {
    MaterialPhysics* material_physics = (MaterialPhysics*)malloc(sizeof(MaterialPhysics));
    if (!material_physics) return NULL;
    material_physics->friction_coefficient = friction;
    material_physics->restitution_coefficient = restitution;
    material_physics->density = density;
    return material_physics;
}

void MaterialPhysics_Destroy(MaterialPhysics* material_physics) {
    if (material_physics) {
        free(material_physics);
    }
}
