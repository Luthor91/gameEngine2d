#ifndef IMPULSE_H
#define IMPULSE_H

#define DEFAULT_MAX_IMPULSES 2048

/**
 * Représente une impulsion avec une magnitude, une direction, une durée et un temps écoulé.
 */
typedef struct Impulse {
    float magnitude; ///< Magnitude de l'impulsion.
    float direction; ///< Direction de l'impulsion en radians.
    float duration; ///< Durée de l'impulsion en secondes.
    float timeElapsed; ///< Temps écoulé depuis le début de l'impulsion en secondes.
} Impulse;

/**
 * Représente un gestionnaire d'impulsions, qui gère un ensemble d'impulsions.
 */
typedef struct ImpulseManager {
    Impulse** impulses; ///< Tableau de pointeurs vers les impulsions gérées par le gestionnaire.
    int max_impulses; ///< Nombre maximum d'impulsions que le gestionnaire peut contenir.
    int index; ///< Index actuel dans le tableau des impulsions, pour ajouter de nouvelles impulsions.
} ImpulseManager;

/**
 * Initialise une nouvelle impulsion avec une magnitude, une direction et une durée spécifiées.
 *
 * @param magnitude Magnitude de l'impulsion.
 * @param direction Direction de l'impulsion en radians.
 * @param duration Durée de l'impulsion en secondes.
 * @return Pointeur vers la nouvelle instance de Impulse.
 */
Impulse* Impulse_Init(float magnitude, float direction, float duration);

/**
 * Libère la mémoire allouée pour une instance d'Impulsion.
 *
 * @param impulse Pointeur vers l'impulsion à détruire.
 */
void Impulse_Destroy(Impulse* impulse);

/**
 * Initialise un gestionnaire d'impulsions avec une capacité maximale spécifiée.
 *
 * @param max_impulses Nombre maximum d'impulsions que le gestionnaire peut contenir.
 * @return Pointeur vers le gestionnaire d'impulsions nouvellement créé.
 */
ImpulseManager* ImpulseManager_Init(int max_impulses);

/**
 * Libère la mémoire allouée pour un gestionnaire d'impulsions et toutes ses impulsions.
 *
 * @param manager Pointeur vers le gestionnaire d'impulsions à détruire.
 */
void ImpulseManager_Destroy(ImpulseManager* manager);

/**
 * Ajoute une impulsion au gestionnaire d'impulsions.
 *
 * @param manager Pointeur vers le gestionnaire d'impulsions.
 * @param impulse Pointeur vers l'impulsion à ajouter au gestionnaire.
 */
void ImpulseManager_AddImpulse(ImpulseManager* manager, Impulse* impulse);

#endif // IMPULSE_H
