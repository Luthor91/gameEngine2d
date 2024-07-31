#ifndef FORCE_H
#define FORCE_H

#include <math.h>

/**
 * Représente une force avec une magnitude et une direction.
 */
typedef struct Force {
    float magnitude; ///< Magnitude de la force en unités de mesure.
    float direction; ///< Direction de la force en radians ou degrés.
} Force;

/**
 * Représente un gestionnaire de forces, qui gère un ensemble de forces.
 */
typedef struct ForceManager {
    Force** forces; ///< Tableau de pointeurs vers les forces gérées par le gestionnaire.
    int max_force; ///< Nombre maximum de forces que le gestionnaire peut contenir.
    int index; ///< Index actuel de la force dans le tableau.
} ForceManager;

/**
 * Initialise une nouvelle force avec une magnitude et une direction spécifiées.
 *
 * @param magnitude Magnitude de la force.
 * @param direction Direction de la force en radians ou degrés.
 * @return Pointeur vers la nouvelle instance de Force.
 */
Force* Force_Init(float magnitude, float direction);

/**
 * Libère la mémoire allouée pour une instance de Force.
 *
 * @param force Pointeur vers la force à détruire.
 */
void Force_Destroy(Force* force);

/**
 * Initialise un gestionnaire de forces avec une capacité maximale spécifiée.
 *
 * @param max_force Nombre maximum de forces que le gestionnaire peut contenir.
 * @return Pointeur vers le gestionnaire de forces nouvellement créé.
 */
ForceManager* ForceManager_Init(int max_force);

/**
 * Ajoute une force au gestionnaire de forces.
 *
 * @param manager Pointeur vers le gestionnaire de forces.
 * @param force Pointeur vers la force à ajouter.
 */
void ForceManager_AddForce(ForceManager* manager, Force* force);

/**
 * Calcule la force nette résultante de toutes les forces dans le gestionnaire.
 *
 * @param manager Pointeur vers le gestionnaire de forces.
 * @return Pointeur vers la force nette résultante.
 */
Force* ForceManager_CalculateNetForce(ForceManager* manager);

#endif // FORCE_H
