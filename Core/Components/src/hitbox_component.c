#include "../include/hitbox_component.h"

void addHitboxComponent(Entity entity, float offsetX, float offsetY, float width, float height) {
    if (entity >= 0 && entity < MAX_ENTITIES) {
        hitboxComponents[entity] = (HitboxComponent){offsetX, offsetY, width, height};
        hasHitbox[entity] = true;
    }
}

HitboxComponent* getHitboxComponent(Entity entity) {
    if (entity >= 0 && entity < MAX_ENTITIES && hasHitbox[entity]) {
        return &hitboxComponents[entity];
    }
    return NULL;
}

bool checkCollision(Entity entity1, Entity entity2) {
    if (!hasHitbox[entity1] || !hasHitbox[entity2]) return false;

    HitboxComponent* hitbox1 = getHitboxComponent(entity1);
    HitboxComponent* hitbox2 = getHitboxComponent(entity2);
    
    PositionComponent* pos1 = getPositionComponent(entity1);
    PositionComponent* pos2 = getPositionComponent(entity2);
    
    float x1 = pos1->x + hitbox1->offsetX;
    float y1 = pos1->y + hitbox1->offsetY;
    float x2 = pos2->x + hitbox2->offsetX;
    float y2 = pos2->y + hitbox2->offsetY;

    return (x1 < x2 + hitbox2->width && 
            x1 + hitbox1->width > x2 && 
            y1 < y2 + hitbox2->height && 
            y1 + hitbox1->height > y2);
}