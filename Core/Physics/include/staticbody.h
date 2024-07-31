#ifndef STATICBODY_H
#define STATICBODY_H

#include "../../Spatial/include/transform.h"
#include "physics.h"

/**
 * Représente un corps statique avec des propriétés physiques et une transformation spatiale.
 */
typedef struct StaticBody {
    Physics* physics; ///< Pointeur vers les propriétés physiques du corps statique.
    Transform* transform; ///< Pointeur vers la transformation spatiale du corps statique (position, taille, etc.).
} StaticBody;

/**
 * Gestionnaire pour les corps statiques.
 */
typedef struct StaticBodyManager {
    StaticBody** staticBodies; ///< Tableau de pointeurs vers les corps statiques gérés.
    int max_body; ///< Nombre maximal de corps statiques pouvant être gérés.
    int index; ///< Index actuel pour ajouter de nouveaux corps statiques.
} StaticBodyManager;

/**
 * Initialise un corps statique avec la transformation et les propriétés physiques spécifiées.
 *
 * @param transform Pointeur vers la transformation spatiale du corps statique.
 * @param physics Pointeur vers les propriétés physiques du corps statique.
 * @return Pointeur vers le corps statique initialisé.
 */
StaticBody* StaticBody_Init(Transform* transform, Physics* physics);

/**
 * Détruit un corps statique, libérant les ressources associées.
 *
 * @param body Pointeur vers le corps statique à détruire.
 */
void StaticBody_Destroy(StaticBody* body);

/**
 * Initialise un gestionnaire de corps statiques avec un nombre maximal spécifié.
 *
 * @param max_body Nombre maximal de corps statiques que le gestionnaire peut contenir.
 * @return Pointeur vers le gestionnaire de corps statiques initialisé.
 */
StaticBodyManager* StaticBodyManager_Init(int max_body);

/**
 * Ajoute un corps statique au gestionnaire de corps statiques.
 *
 * @param manager Pointeur vers le gestionnaire de corps statiques.
 * @param body Pointeur vers le corps statique à ajouter.
 */
void StaticBodyManager_AddBody(StaticBodyManager* manager, StaticBody* body);

/**
 * Détruit le gestionnaire de corps statiques, libérant les ressources associées.
 *
 * @param manager Pointeur vers le gestionnaire de corps statiques à détruire.
 */
void StaticBodyManager_Destroy(StaticBodyManager* manager);

#endif // STATICBODY_H
