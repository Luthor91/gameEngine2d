#include "../include/collision_system.h"

// Fonction pour initialiser le système de collision (si nécessaire)
void initCollisionSystem() {
    // Initialisation spécifique si nécessaire
}

// Fonction pour mettre à jour le système de collision
void updateCollisionSystem() {
    // Parcourir toutes les entités et vérifier les collisions
    for (Entity entity1 = 0; entity1 < MAX_ENTITIES; ++entity1) {
        if (!hasHitbox[entity1]) continue;

        for (Entity entity2 = entity1 + 1; entity2 < MAX_ENTITIES; ++entity2) {
            if (!hasHitbox[entity2]) continue;

            if (checkCollision(entity1, entity2)) {
                // Gérer la collision ici (par exemple, envoyer un événement, infliger des dégâts, etc.)
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

    // Calculer les positions des hitbox
    float leftA = pos1->x + hitbox1->offsetX;
    float rightA = leftA + hitbox1->width;
    float topA = pos1->y + hitbox1->offsetY;
    float bottomA = topA + hitbox1->height;

    float leftB = pos2->x + hitbox2->offsetX;
    float rightB = leftB + hitbox2->width;
    float topB = pos2->y + hitbox2->offsetY;
    float bottomB = topB + hitbox2->height;

    // Vérifier les chevauchements des rectangles (AABB collision detection)
    if (rightA <= leftB || leftA >= rightB || bottomA <= topB || topA >= bottomB) {
        return false;
    }
    
    return true;
}
