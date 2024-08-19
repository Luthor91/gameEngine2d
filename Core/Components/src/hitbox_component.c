#include "../include/hitbox_component.h"

static HitboxComponent hitboxComponents[MAX_ENTITIES];

void addHitboxComponent(Entity entity, HitboxComponent hitbox) {
    if (entity >= 0 && entity < MAX_ENTITIES) {
        hitboxComponents[entity] = hitbox;
        hasHitbox[entity] = true;
    }
}

HitboxComponent* getHitboxComponent(Entity entity) {
    if (entity < MAX_ENTITIES && hasHitbox[entity]) {
        return &hitboxComponents[entity];
    }
    return NULL;
}

void updateHitbox(Entity entity) {
    PositionComponent* position = getPositionComponent(entity);
    SizeComponent* size = getSizeComponent(entity);
    HitboxComponent* hitbox = getHitboxComponent(entity);
    
    if (position && size && hitbox) {
        hitbox->x = position->x;
        hitbox->y = position->y;
        hitbox->width = size->width;
        hitbox->height = size->height;
    }
}
