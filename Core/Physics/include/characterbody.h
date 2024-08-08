#ifndef CHARACTERBODY_H
#define CHARACTERBODY_H

#include "../../Spatial/include/transform.h"
#include "physics.h"

#define DEFAULT_CHARACTERBODY CharacterBodyManager_Init(DEFAULT_MAX_BODIES)

/**
 * Représente un corps charactere avec des propriétés physiques et une transformation spatiale.
 */
typedef struct CharacterBody {
    Physics* physics; ///< Pointeur vers les propriétés physiques du corps charactere.
    Transform* transform; ///< Pointeur vers la transformation spatiale du corps charactere (position, taille, etc.).
} CharacterBody;

/**
 * Gestionnaire pour les corps characteres.
 */
typedef struct CharacterBodyManager {
    CharacterBody** bodies; ///< Tableau de pointeurs vers les corps characteres gérés.
    int max_body; ///< Nombre maximal de corps characteres pouvant être gérés.
    int index; ///< Index actuel pour ajouter de nouveaux corps characteres.
} CharacterBodyManager;

/**
 * Initialise un gestionnaire de corps characteres avec un nombre maximal spécifié.
 *
 * @param max_body Nombre maximal de corps characteres que le gestionnaire peut contenir.
 * @return Pointeur vers le gestionnaire de corps characteres initialisé.
 */
CharacterBodyManager* CharacterBodyManager_Init(int max_body);

/**
 * Initialise un corps charactere avec la transformation et les propriétés physiques spécifiées.
 *
 * @param transform Pointeur vers la transformation spatiale du corps charactere.
 * @param physics Pointeur vers les propriétés physiques du corps charactere.
 * @return Pointeur vers le corps charactere initialisé.
 */
CharacterBody* CharacterBody_Init(Transform* transform, Physics* physics);

void CharacterBodyManager_Add(CharacterBodyManager* manager, ...);

void CharacterBodyManager_Update(CharacterBodyManager* manager, float deltaTime);

/**
 * Met à jour les propriétés d'un corps charactere en fonction du temps écoulé.
 *
 * @param body Pointeur vers le corps charactere à mettre à jour.
 * @param deltaTime Temps écoulé depuis la dernière mise à jour (en secondes).
 */
void CharacterBody_Update(CharacterBody* body, float deltaTime);

#endif // CHARACTERBODY_H
