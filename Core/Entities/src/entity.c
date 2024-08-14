#include "../include/entity.h"

bool entityStates[MAX_ENTITIES] = { false };
bool hasSprite[MAX_ENTITIES] = { false };
bool hasPosition[MAX_ENTITIES] = { false };
bool hasVelocity[MAX_ENTITIES] = { false };
bool hasInput[MAX_ENTITIES] = { false };
bool hasTransform[MAX_ENTITIES] = { false };
bool hasAnimation[MAX_ENTITIES] = { false };
bool hasHitbox[MAX_ENTITIES] = { false };
bool hasSize[MAX_ENTITIES] = { false };
bool hasTags[MAX_ENTITIES] = { false };
Entity playerEntity = 0;

static Entity nextEntityID = 0;

Entity createEntity() {
    if (nextEntityID >= MAX_ENTITIES) {
        return -1; // Indique que la création de l'entité a échoué
    }
    Entity newEntity = nextEntityID++;
    entityStates[newEntity] = true;
    return newEntity;
}

Entity getEntity(int id) {
    if (id < 0 || id >= MAX_ENTITIES) {
        return INVALID_ENTITY_ID;
    }
    return (Entity)id;
}

void disableEntity(Entity entity) {
    if (entity < MAX_ENTITIES && entityStates[entity]) {
        // Désactiver les composants
        entityStates[entity] = false;
        hasPosition[entity] = false;
        hasVelocity[entity] = false;
        hasSprite[entity] = false;
        hasInput[entity] = false;
        hasTransform[entity] = false;
        hasAnimation[entity] = false;
        hasHitbox[entity] = false;
        hasSize[entity] = false;
        hasTags[entity] = false;

        removeAllTags(entity);
    }
}

void destroyEntity(Entity entity) {
    if (entity < MAX_ENTITIES && entityStates[entity]) {
        // Désactiver les composants
        entityStates[entity] = false;
        hasPosition[entity] = false;
        hasVelocity[entity] = false;
        hasSprite[entity] = false;
        hasInput[entity] = false;
        hasTransform[entity] = false;
        hasAnimation[entity] = false;
        hasHitbox[entity] = false;
        hasSize[entity] = false;
    }
}

bool hasPositionComponent(Entity entity) {
    return hasPosition[entity];
}

bool hasVelocityComponent(Entity entity) {
    return hasVelocity[entity];
}

bool hasSpriteComponent(Entity entity) {
    return hasSprite[entity];
}

bool hasInputComponent(Entity entity) {
    return hasInput[entity];
}

bool hasTransformComponent(Entity entity) {
    return hasTransform[entity];
}

bool hasAnimationComponent(Entity entity) {
    return hasAnimation[entity];
}

bool hasHitboxComponent(Entity entity) {
    return hasHitbox[entity];
}

bool hasSizeComponent(Entity entity) {
    return hasSize[entity];
}

bool hasTagComponent(Entity entity) {
    return hasTags[entity];
}
