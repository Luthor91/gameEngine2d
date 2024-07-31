#ifndef MATERIAL_H
#define MATERIAL_H

/**
 * Représente les propriétés physiques d'un matériau utilisé dans les simulations.
 */
typedef struct Material {
    float friction_coefficient; ///< Coefficient de friction du matériau, utilisé pour calculer la résistance au glissement entre surfaces.
    float restitution_coefficient; ///< Coefficient de restitution du matériau, utilisé pour déterminer la quantité d'énergie conservée lors des collisions.
    float density; ///< Densité du matériau, utilisée pour calculer la masse volumique.
    float mass; ///< Masse totale du matériau.
    float friction; ///< Valeur spécifique de friction pour le matériau.
    float restitution; ///< Valeur spécifique de restitution (rebondissement) pour le matériau.
} Material;

/**
 * Initialise un matériau avec les propriétés physiques spécifiées.
 *
 * @param friction_coefficient Coefficient de friction du matériau.
 * @param restitution_coefficient Coefficient de restitution pour les collisions.
 * @param density Densité du matériau.
 * @param mass Masse totale du matériau.
 * @param friction Valeur spécifique de friction pour le matériau.
 * @param restitution Valeur spécifique de restitution (rebondissement) pour le matériau.
 * @return Pointeur vers la nouvelle instance de Material initialisée.
 */
Material* Material_Init(float friction_coefficient, float restitution_coefficient, float density, float mass, float friction, float restitution);

/**
 * Libère la mémoire allouée pour une instance de Material.
 *
 * @param material Pointeur vers le matériau à détruire.
 */
void Material_Destroy(Material* material);

#endif // MATERIAL_H
