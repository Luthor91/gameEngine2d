#ifndef VECTOR2_H
#define VECTOR2_H

#define VECTOR2_ZERO Vector2_Init(0.0f, 0.0f)

/**
 * @brief Structure représentant un vecteur 2D.
 */
typedef struct Vector2 {
    float x; ///< Composante x du vecteur.
    float y; ///< Composante y du vecteur.
} Vector2;

/**
 * @brief Initialise un nouveau vecteur 2D avec les valeurs spécifiées.
 * 
 * @param x Valeur de la composante x du vecteur.
 * @param y Valeur de la composante y du vecteur.
 * @return Un pointeur vers la nouvelle instance de `Vector2`, ou NULL en cas d'échec.
 */
Vector2* Vector2_Init(float x, float y);

/**
 * @brief Libère la mémoire allouée pour un vecteur 2D.
 * 
 * @param vector Pointeur vers le vecteur à libérer.
 */
void Vector2_Destroy(Vector2* vector);

#endif // VECTOR2_H
