#ifndef COLLISION_H
#define COLLISION_H

#include "physics.h"
#include "rigidbody.h"
#include "staticbody.h"
#include "physicsbodies.h"
#include "hitbox.h"
#include "../../Spatial/include/point2d.h"
#include "../../Events/include/timer_manager.h"

/**
 * Vérifie la collision entre deux objets circulaires.
 *
 * @param posA Pointeur vers la position du premier objet.
 * @param posB Pointeur vers la position du deuxième objet.
 * @param radiusA Rayon du premier objet.
 * @param radiusB Rayon du deuxième objet.
 * @return 1 si une collision est détectée, 0 sinon.
 */
int Collision_Check(Hitbox* hitboxA, Hitbox* hitboxB);

/**
 * Gère la collision entre un corps rigide et un corps statique.
 *
 * @param body Pointeur vers le corps rigide impliqué dans la collision.
 * @param staticBody Pointeur vers le corps statique impliqué dans la collision.
 */
void Collision_Handle(Physics* physics_body_1, Transform* transform_body_1, Hitbox* hitbox_body_1, 
                      Physics* physics_body_2, Transform* transform_body_2, Hitbox* hitbox_body_2);

void Collision_HandleAll(PhysicsBodies* physics_bodies);

#endif // COLLISION_H
