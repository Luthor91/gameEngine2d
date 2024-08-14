#include "../include/transform_component.h"

static TransformComponent transformComponents[MAX_ENTITIES];

void addTransformComponent(Entity entity, TransformComponent transform) {
    if (entity < MAX_ENTITIES) {
        transformComponents[entity] = transform;
        hasTransform[entity] = true;
    }
}

TransformComponent* getTransformComponent(Entity entity) {
    if (entity < MAX_ENTITIES && hasTransform[entity]) {
        return &transformComponents[entity];
    }
    return NULL;
}
