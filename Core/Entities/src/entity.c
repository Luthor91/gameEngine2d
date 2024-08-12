#include "../include/entity.h"

static Entity lastEntity = 0;

Entity createEntity() {
    return lastEntity++;
}

void destroyEntity(Entity entity) {
    // Implémentez la destruction de l'entité
}