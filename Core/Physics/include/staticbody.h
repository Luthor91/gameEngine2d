#ifndef STATICBODY_H
#define STATICBODY_H

#include "../../Spatial/include/transform.h"
#include "physics.h"

#define DEFAULT_STATICBODY StaticBodyManager_Init(DEFAULT_MAX_BODIES)

/**
 * Représente un corps statice avec des propriétés physiques et une transformation spatiale.
 */
typedef struct StaticBody {
    Physics* physics; ///< Pointeur vers les propriétés physiques du corps statice.
    Transform* transform; ///< Pointeur vers la transformation spatiale du corps statice (position, taille, etc.).
} StaticBody;

/**
 * Gestionnaire pour les corps statices.
 */
typedef struct StaticBodyManager {
    StaticBody** bodies; ///< Tableau de pointeurs vers les corps statices gérés.
    int max_body; ///< Nombre maximal de corps statices pouvant être gérés.
    int index; ///< Index actuel pour ajouter de nouveaux corps statices.
} StaticBodyManager;

/**
 * Initialise un gestionnaire de corps statices avec un nombre maximal spécifié.
 *
 * @param max_body Nombre maximal de corps statices que le gestionnaire peut contenir.
 * @return Pointeur vers le gestionnaire de corps statices initialisé.
 */
StaticBodyManager* StaticBodyManager_Init(int max_body);

/**
 * Initialise un corps statice avec la transformation et les propriétés physiques spécifiées.
 *
 * @param transform Pointeur vers la transformation spatiale du corps statice.
 * @param physics Pointeur vers les propriétés physiques du corps statice.
 * @return Pointeur vers le corps statice initialisé.
 */
StaticBody* StaticBody_Init(Transform* transform, Physics* physics);

void StaticBodyManager_Add(StaticBodyManager* manager, ...);

void StaticBodyManager_Update(StaticBodyManager* manager, float deltaTime);

/**
 * Met à jour les propriétés d'un corps statice en fonction du temps écoulé.
 *
 * @param body Pointeur vers le corps statice à mettre à jour.
 * @param deltaTime Temps écoulé depuis la dernière mise à jour (en secondes).
 */
void StaticBody_Update(StaticBody* body, float deltaTime);

#endif // STATICBODY_H
