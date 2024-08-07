#ifndef PHYSICSBODIES_H
#define PHYSICSBODIES_H

#include "physics.h"
#include "rigidbody.h"
#include "staticbody.h"
#include "characterbody.h"

/**
 * Représente un corps rigide avec des propriétés physiques et une transformation spatiale.
 */
typedef struct PhysicsBodies {
    CharacterBodyManager* cb_manager;
    RigidBodyManager* rb_manager;
    StaticBodyManager* sb_manager; 
} PhysicsBodies;


/**
 * Initialise un gestionnaire de corps rigides avec un nombre maximal spécifié.
 *
 * @param max_body Nombre maximal de corps rigides que le gestionnaire peut contenir.
 * @return Pointeur vers le gestionnaire de corps rigides initialisé.
 */
PhysicsBodies* PhysicBodies_Init(CharacterBodyManager* cb_manager, RigidBodyManager* rb_manager, StaticBodyManager* sb_manager);

void PhysicBodies_Update(PhysicsBodies* physics_bodies, float deltaTime);

#endif // PHYSICSBODIES_H
