#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "../../Spatial/include/transform.h"
#include "physics.h"

/**
 * Représente un corps rigide avec des propriétés physiques et une transformation spatiale.
 */
typedef struct RigidBody {
    Physics* physics; ///< Pointeur vers les propriétés physiques du corps rigide.
    Transform* transform; ///< Pointeur vers la transformation spatiale du corps rigide (position, taille, etc.).
} RigidBody;

/**
 * Gestionnaire pour les corps rigides.
 */
typedef struct RigidBodyManager {
    RigidBody** rigidBodies; ///< Tableau de pointeurs vers les corps rigides gérés.
    int max_body; ///< Nombre maximal de corps rigides pouvant être gérés.
    int index; ///< Index actuel pour ajouter de nouveaux corps rigides.
} RigidBodyManager;

/**
 * Initialise un gestionnaire de corps rigides avec un nombre maximal spécifié.
 *
 * @param max_body Nombre maximal de corps rigides que le gestionnaire peut contenir.
 * @return Pointeur vers le gestionnaire de corps rigides initialisé.
 */
RigidBodyManager* RigidBodyManager_Init(int max_body);

/**
 * Initialise un corps rigide avec la transformation et les propriétés physiques spécifiées.
 *
 * @param transform Pointeur vers la transformation spatiale du corps rigide.
 * @param physics Pointeur vers les propriétés physiques du corps rigide.
 * @return Pointeur vers le corps rigide initialisé.
 */
RigidBody* RigidBody_Init(Transform* transform, Physics* physics);

void RigidBodyManager_Add(RigidBodyManager* manager, ...);

void RigidBodyManager_Update(RigidBodyManager* manager, float deltaTime);

/**
 * Met à jour les propriétés d'un corps rigide en fonction du temps écoulé.
 *
 * @param body Pointeur vers le corps rigide à mettre à jour.
 * @param deltaTime Temps écoulé depuis la dernière mise à jour (en secondes).
 */
void RigidBody_Update(RigidBody* body, float deltaTime);

#endif // RIGIDBODY_H
