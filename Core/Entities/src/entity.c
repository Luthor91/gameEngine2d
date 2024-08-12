#include "../include/entity.h"



Entity createEntity() {
    if (nextEntityID >= MAX_ENTITIES) {
        return -1; // Indique que la création de l'entité a échoué
    }
    Entity newEntity = nextEntityID++;
    entityStates[newEntity] = true;
    return newEntity;
}

void destroyEntity(Entity entity) {
    if (entity < MAX_ENTITIES && entityStates[entity]) {
        entityStates[entity] = false;
        hasPosition[entity] = false;
        hasVelocity[entity] = false;
        hasSprite[entity] = false;
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