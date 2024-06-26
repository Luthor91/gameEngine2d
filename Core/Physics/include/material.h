#ifndef MATERIAL_H
#define MATERIAL_H

typedef struct Material {
    float friction_coefficient;  // Coefficient de friction du matériau
    float restitution_coefficient; // Coefficient de restitution pour les collisions
    float density;               // Densité du matériau
    float mass;
    float friction;
    float restitution;  // bounce
} Material;

Material* Material_Init(float friction_coefficient, float restitution_coefficient, float density, float mass, float friction, float restitution);
void Material_Destroy(Material* material);

#endif // MATERIAL_H
