#include "../include/collision_system.h"

// Fonction pour initialiser le système de collision (si nécessaire)
void initCollisionSystem() {
    // Initialisation spécifique si nécessaire
}

CollisionData* CollisionData_Init(Entity entity1, Entity entity2) {
    CollisionData* collider = (CollisionData*)malloc(sizeof(CollisionData));
    if (collider == NULL) {
        printf("Memory allocation failed for collider1\n");
        return NULL;
    }
    collider->entity1 = entity1;
    collider->entity2 = entity2;

    return collider;
}

// Fonction pour mettre à jour le système de collision
void updateCollisionSystem() {
    // Parcourir toutes les entités et vérifier les collisions
    for (Entity entity1 = 0; entity1 < MAX_ENTITIES; ++entity1) {
        if (!hasHitbox[entity1] || !hasPosition[entity1]) continue;

        for (Entity entity2 = entity1 + 1; entity2 < MAX_ENTITIES; ++entity2) {
            if (!hasHitbox[entity2] || !hasPosition[entity2]) continue;

                if (checkCollision(entity1, entity2)) {
                    CollisionData* collider1 = CollisionData_Init(entity1, entity2);
                    Event collisionEvent1 = { EVENT_TYPE_COLLIDE, collider1 };
                    emitEvent(collisionEvent1);

                    CollisionData* collider2 = CollisionData_Init(entity2, entity1);
                    Event collisionEvent2 = { EVENT_TYPE_COLLIDE, collider2 };
                    emitEvent(collisionEvent2);
                }
        }
    }
}

// Fonction pour vérifier la collision entre deux entités
bool checkCollision(Entity entity1, Entity entity2) {

    HitboxComponent* hitbox1 = getHitboxComponent(entity1);
    HitboxComponent* hitbox2 = getHitboxComponent(entity2);

    PositionComponent* pos1 = getPositionComponent(entity1);
    PositionComponent* pos2 = getPositionComponent(entity2);

    if (!hitbox1 || !hitbox2 || !pos1 || !pos2) {
        printf("Error: Missing components for entities %d or %d\n", entity1, entity2);
        return false;
    }

    // Calculer les positions des hitboxes
    float leftA = pos1->x + hitbox1->x;
    float rightA = leftA + hitbox1->width;
    float topA = pos1->y + hitbox1->y;
    float bottomA = topA + hitbox1->height;

    float leftB = pos2->x + hitbox2->x;
    float rightB = leftB + hitbox2->width;
    float topB = pos2->y + hitbox2->y;
    float bottomB = topB + hitbox2->height;

    // Vérifier les chevauchements des rectangles (AABB collision detection)
    if (rightA <= leftB || leftA >= rightB || bottomA <= topB || topA >= bottomB) {
        return false;
    }

    return true;
}
