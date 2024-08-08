#ifndef VELOCITY_H
#define VELOCITY_H

#define VELOCITY_ZERO Velocity_Init(0.0f, 0.0f)

/**
 * Représente la vitesse d'un objet en deux dimensions.
 */
typedef struct Velocity {
    float x; ///< Composante de la vitesse sur l'axe X.
    float y; ///< Composante de la vitesse sur l'axe Y.
} Velocity;

/**
 * Initialise une structure de vitesse avec les valeurs spécifiées.
 *
 * @param x Composante de la vitesse sur l'axe X.
 * @param y Composante de la vitesse sur l'axe Y.
 * @return Pointeur vers la structure de vitesse initialisée.
 */
Velocity* Velocity_Init(float x, float y);

/**
 * Détruit une structure de vitesse, libérant les ressources associées.
 *
 * @param velocity Pointeur vers la structure de vitesse à détruire.
 */
void Velocity_Destroy(Velocity* velocity);

#endif // VELOCITY_H
