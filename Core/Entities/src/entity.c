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

    // Copier les drapeaux indiquant les composants présents
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

    // Copier chaque composant avec une copie indépendante
    if (hasAnimationComponent(entity)) {
        AnimationComponent original = *getAnimationComponent(entity);
        AnimationComponent new = {original.currentFrame, original.totalFrames, original.frameDuration, original.lastFrameTime, original.is_active};
        addAnimationComponent(new_entity, new); // Copie profonde des champs si nécessaire
    }
    if (hasPositionComponent(entity)) {
        PositionComponent original = *getPositionComponent(entity);
        PositionComponent new = {original.x, original.y};
        addPositionComponent(new_entity, original); // Copie profonde des champs
    }
    if (hasVelocityComponent(entity)) {
        VelocityComponent original = *getVelocityComponent(entity);
        VelocityComponent new = {original.x, original.y};
        addVelocityComponent(new_entity, original);
    }
    if (hasSpriteComponent(entity)) {
        SpriteComponent original = *getSpriteComponent(entity);
        SpriteComponent new = {original.texture, original.srcRect};
        addSpriteComponent(new_entity, original);
    }
    if (hasInputComponent(entity)) {
        InputComponent original = *getInputComponent(entity);
        InputComponent new = {original.keys};
        addInputComponent(new_entity, original);
    }
    if (hasTransformComponent(entity)) {
        TransformComponent original = *getTransformComponent(entity);
        TransformComponent new = {original.x, original.y, original.scaleX, original.scaleY, original.rotation};
        addTransformComponent(new_entity, original);
    }
    if (hasHitboxComponent(entity)) {
        HitboxComponent original = *getHitboxComponent(entity);
        HitboxComponent new = {original.x, original.y, original.width, original.height, original.is_active};
        addHitboxComponent(new_entity, original);
    }
    if (hasSizeComponent(entity)) {
        SizeComponent original = *getSizeComponent(entity);
        SizeComponent new = {original.width, original.height};
        addSizeComponent(new_entity, original);
    }
    if (hasDataComponents(entity)) {
        DataComponent original = *getDataComponent(entity);
        DataComponent new = {original.values[DATA_MAX+128]};
        addDataComponent(new_entity, original);
    }
    if (hasTagComponent(entity)) {
        TagComponent original = *getTagComponent(entity);
        TagComponent new = {original.tags[MAX_TAGS][MAX_TAG_LENGTH], original.tagCount};
        addTagComponent(new_entity, original);
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
    if (!isEntityValid(entity)) {
        return false;
    }
    
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
