#ifndef COLLISION_H
#define COLLISION_H

#include "physics.h"
#include "rigidbody.h"
#include "staticbody.h"
#include "../../Spatial/include/point2d.h"

/**
 * Vérifie la collision entre deux objets circulaires.
 *
 * @param posA Pointeur vers la position du premier objet.
 * @param posB Pointeur vers la position du deuxième objet.
 * @param radiusA Rayon du premier objet.
 * @param radiusB Rayon du deuxième objet.
 * @return 1 si une collision est détectée, 0 sinon.
 */
int Collision_Check(Point2D* posA, Point2D* posB, float radiusA, float radiusB);

/**
 * Gère la collision entre un corps rigide et un corps statique.
 *
 * @param body Pointeur vers le corps rigide impliqué dans la collision.
 * @param staticBody Pointeur vers le corps statique impliqué dans la collision.
 */
void Collision_Handle(RigidBody* body, StaticBody* staticBody);

#endif // COLLISION_H
