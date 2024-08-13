#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "../../Components/include/hitbox_component.h"
#include "../../Components/include/position_component.h"

// Fonction pour initialiser le système de collision (si nécessaire)
void initCollisionSystem();

// Fonction pour mettre à jour le système de collision
void updateCollisionSystem();

// Fonction pour vérifier la collision entre deux entités
bool checkCollision(Entity entity1, Entity entity2);

#endif // COLLISION_SYSTEM_H
