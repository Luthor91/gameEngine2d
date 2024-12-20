#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "../../Components/include/hitbox_component.h"
#include "../../Components/include/position_component.h"
#include "../../Entities/include/entity.h"

typedef struct Event Event;

typedef struct CollisionData {
    Entity entity1;
    Entity entity2;
    float position_x;
    float position_y;
    float direction_x;
    float direction_y;
} CollisionData;

// Fonction pour initialiser le système de collision (si nécessaire)
void initCollisionSystem();

CollisionData* CollisionData_Init(Entity entity1, Entity entity2);

void CollisionData_Free(CollisionData* colliderData);

// Fonction pour mettre à jour le système de collision
void updateCollisionSystem();

// Fonction pour vérifier la collision entre deux entités
bool checkCollision(Entity entity1, Entity entity2);

bool checkCollisionTags(Event event, const char* tag1, const char* tag2);

#endif // COLLISION_SYSTEM_H
