#include "../include/material.h"
#include <stdlib.h>

Material* Material_Init(float friction, float restitution, float density) {
    Material* material = (Material*)malloc(sizeof(Material));
    if (!material) return NULL;
    material->friction_coefficient = friction;
    material->restitution_coefficient = restitution;
    material->density = density;
    return material;
}

void Material_Destroy(Material* material) {
    if (material) {
        free(material);
    }
}
