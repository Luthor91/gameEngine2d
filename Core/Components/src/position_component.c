#include "../include/position_component.h"

static PositionComponent positionComponents[MAX_ENTITIES];

// Fonction pour ajouter un composant Sprite à une entité
void addPositionComponent(Entity entity, PositionComponent position) {
    if (entity < MAX_ENTITIES) {
        positionComponents[entity] = position;
        hasPosition[entity] = true;
    }
}

PositionComponent* getPositionComponent(Entity entity) {
    if (entity < MAX_ENTITIES && hasPosition[entity]) {
        return &positionComponents[entity];
    }
    return NULL;
}

