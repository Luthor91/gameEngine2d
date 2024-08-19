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
bool hasDatas[MAX_ENTITIES] = { false };
Entity playerEntity = 0;

static Entity nextEntityID = 0;

Entity createEntity() {
    if (nextEntityID >= MAX_ENTITIES) return INVALID_ENTITY_ID;

    Entity newEntity = nextEntityID++;
    entityStates[newEntity] = true;
    return newEntity;
}

Entity createEntityWithId(int id) {
    if (id >= MAX_ENTITIES) {
        return INVALID_ENTITY_ID; // Indique que la création de l'entité a échoué
    }
    Entity newEntity = (Entity)id;
    entityStates[newEntity] = true;
    return newEntity;
}

Entity copyEntity(Entity entity) {
    Entity new_entity = createEntity();

    if (new_entity == INVALID_ENTITY_ID) return INVALID_ENTITY_ID;
    entityStates[new_entity] = true;
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
    if (id < 0 || id >= MAX_ENTITIES) {
        return INVALID_ENTITY_ID;
    }
    return (Entity)id;
}

Entity getFirstEmptyEntity() {
    // Parcours des entités existantes pour trouver une entité libre
    for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
        if (entityStates[entity] == false) {  // Trouver une entité libre
            entityStates[entity] = true;      // Marquer l'entité comme utilisée
            return entity;                    // Retourner l'ID de l'entité
        }
    }
    
    // Si aucune entité libre n'est trouvée, tenter de créer une nouvelle entité
    if (nextEntityID < MAX_ENTITIES) {
        Entity newEntity = nextEntityID++;
        entityStates[newEntity] = true;        // Marquer l'entité comme utilisée
        return newEntity;
    }
    
    return INVALID_ENTITY_ID;  // Retourner un ID d'entité invalide si aucune entité ne peut être trouvée ou créée
}

Entity getFirstValidEntity() {
    for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
        if(entityStates[entity] == true) {
            return entity;
        }
    }
    return INVALID_ENTITY_ID;
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

void disableEntitiesFromRange(int start, int end) {
    if (start < 0 || end >= MAX_ENTITIES || start > end)  return;

    // Parcourir chaque entité dans la plage spécifiée
    for (int entity = start; entity <= end; entity++) {
        if (entityStates[entity] == true) {
            disableEntity(entity);
        }
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

int getEntityCount() {
    return (int)nextEntityID;
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
