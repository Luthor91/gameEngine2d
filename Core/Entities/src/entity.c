#include "../include/entity.h"

Entity player_entity = 0;

static Entity currentEntityCount = 0;

Entity createEntity() {
    if (currentEntityCount >= MAX_ENTITIES) return INVALID_ENTITY_ID;

    // Rechercher un emplacement libre
    for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
        if (!entityStates[entity]) {
            entityStates[entity] = true;
            currentEntityCount++;
            return entity;
        }
    }

    // Si aucune place libre n'est trouvée
    return INVALID_ENTITY_ID;
}

Entity createEntityWithId(int id) {
    if (id >= MAX_ENTITIES || entityStates[id]) {
        return INVALID_ENTITY_ID; // L'entité avec cet ID est déjà utilisée ou l'ID est invalide
    }
    entityStates[id] = true;
    currentEntityCount++;
    return id;
}

Entity copyEntity(Entity entity) {
    Entity new_entity = createEntity();

    if (new_entity == INVALID_ENTITY_ID) return INVALID_ENTITY_ID;
    
    hasPosition[new_entity] = hasPosition[entity];
    hasVelocity[new_entity] = hasVelocity[entity];
    hasSprite[new_entity] = hasSprite[entity];
    hasInput[new_entity] = hasInput[entity];
    hasTransform[new_entity] = hasTransform[entity];
    hasAnimation[new_entity] = hasAnimation[entity];
    hasHitbox[new_entity] = hasHitbox[entity];
    hasSize[new_entity] = hasSize[entity];
    hasTags[new_entity] = hasTags[entity];
    hasDatas[new_entity] = hasDatas[entity];

    // Copier les composants
    if (hasAnimationComponent(entity)) {
        addAnimationComponent(new_entity, *getAnimationComponent(entity));
    }
    if (hasPositionComponent(entity)) {
        addPositionComponent(new_entity, *getPositionComponent(entity));
    }
    if (hasVelocityComponent(entity)) {
        addVelocityComponent(new_entity, *getVelocityComponent(entity));
    }
    if (hasSpriteComponent(entity)) {
        addSpriteComponent(new_entity, *getSpriteComponent(entity));
    }
    if (hasInputComponent(entity)) {
        addInputComponent(new_entity, *getInputComponent(entity));
    }
    if (hasTransformComponent(entity)) {
        addTransformComponent(new_entity, *getTransformComponent(entity));
    }
    if (hasHitboxComponent(entity)) {
        addHitboxComponent(new_entity, *getHitboxComponent(entity));
    }
    if (hasSizeComponent(entity)) {
        addSizeComponent(new_entity, *getSizeComponent(entity));
    }
    if (hasDataComponents(entity)) {
        addDataComponent(new_entity, *getDataComponent(entity));
    }
    if (hasTagComponent(entity)) {
        addTagComponent(new_entity, *getTagComponent(entity));
    }

    return new_entity;
}

Entity getEntity(int id) {
    if (id < 0 || id >= MAX_ENTITIES || !entityStates[id]) {
        return INVALID_ENTITY_ID;
    }
    return (Entity)id;
}

Entity getFirstEmptyEntity() {
    return createEntity();
}

Entity getFirstValidEntity() {
    for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
        if (entityStates[entity]) {
            return entity;
        }
    }
    return INVALID_ENTITY_ID;
}

void disableComponentEntity(Entity entity) {
    if (entity < MAX_ENTITIES && entityStates[entity]) {
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
        removeAllTimers(entity);
        removeAllEvents(entity);

        currentEntityCount--;
    }
}

void deactivateEntity(Entity entity) {
    if (entity < MAX_ENTITIES && entityStates[entity]) {
        entityStates[entity] = false;
        currentEntityCount--;
    }
}

void activateEntity(Entity entity) {
    if (entity < MAX_ENTITIES && !entityStates[entity]) {
        entityStates[entity] = true;
        currentEntityCount++;
    }
}

void disableComponentEntitiesFromRange(int start, int end) {
    if (start < 0 || end >= MAX_ENTITIES || start > end) return;

    for (int entity = start; entity <= end; entity++) {
        if (entityStates[entity]) {
            disableComponentEntity(entity);
        }
    }
}

void destroyEntity(Entity entity) {
    if (entity < MAX_ENTITIES && entityStates[entity]) {
        entityStates[entity] = false;
        hasPosition[entity] = false;
        hasVelocity[entity] = false;
        hasSprite[entity] = false;
        hasInput[entity] = false;
        hasTransform[entity] = false;
        hasAnimation[entity] = false;
        hasHitbox[entity] = false;
        hasSize[entity] = false;

        currentEntityCount--;
    }
}

int getEntityCount() {
    return (int)currentEntityCount;
}

bool isEntityValid(Entity entity) {
    return entity < MAX_ENTITIES && entityStates[entity] && entity != INVALID_ENTITY_ID;
}

bool isEntityEnabled(Entity entity) {
    return entityStates[entity];
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

bool hasDataComponents(Entity entity) {
    return hasDatas[entity];
}
