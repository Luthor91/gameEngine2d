#include "../include/transform_component.h"

static TransformComponent transformComponents[MAX_ENTITIES];

TransformComponent* getTransformComponent(Entity entity) {
    if (entity < MAX_ENTITIES) {
        return &transformComponents[entity];
    }
    return NULL;
}

void addTransformComponent(Entity entity, TransformComponent transform) {
    if (entity < MAX_ENTITIES) {
        transformComponents[entity] = transform;
    }
}
