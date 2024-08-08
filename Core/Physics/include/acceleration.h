#ifndef ACCELERATION_H
#define ACCELERATION_H

#include "../../Spatial/include/vector2.h"

#define ACCELERATION_ZERO Acceleration_Init(VECTOR2_ZERO)

// Structure représentant une accélération en 2D.
// Contient les composantes x et y de l'accélération.
typedef struct Acceleration {
    float x; ///< Composante x de l'accélération.
    float y; ///< Composante y de l'accélération.
} Acceleration;

/**
 * @brief Initialise une structure `Acceleration` avec les valeurs données.
 * 
 * @param accel Un pointeur vers une structure `Vector2` contenant les valeurs d'accélération.
 * @return Acceleration* Un pointeur vers la structure `Acceleration` nouvellement créée.
 *         Retourne NULL en cas d'échec d'allocation de mémoire.
 */
Acceleration* Acceleration_Init(Vector2* accel);

/**
 * @brief Détruit une structure `Acceleration` et libère la mémoire associée.
 * 
 * @param acceleration Un pointeur vers la structure `Acceleration` à détruire.
 */
void Acceleration_Destroy(Acceleration* acceleration);

#endif // ACCELERATION_H
