#include "../include/material.h"
#include <stdlib.h>

Material* Material_Init(float friction_coefficient, float restitution_coefficient, float density, float mass, float friction, float restitution) {
    // Allouer de la mémoire pour un nouvel objet Material
    Material* new_material = (Material*)malloc(sizeof(Material));
    if (new_material == NULL) {
        // Gestion d'erreur si l'allocation échoue
        return NULL;
    }

    // Initialiser les champs de la structure Material
    new_material->friction_coefficient = friction_coefficient;
    new_material->restitution_coefficient = restitution_coefficient;
    new_material->density = density;
    new_material->mass = mass;
    new_material->friction = friction;
    new_material->restitution = restitution;

    return new_material;
}

void Material_Destroy(Material* material) {
    if (material) {
        free(material);
    }
}
