#include "../include/position_component.h"

static PositionComponent positionComponents[MAX_ENTITIES];

// Fonction pour ajouter un composant Sprite à une entité
void addPositionComponent(Entity entity, float x, float y) {
    if (entity < MAX_ENTITIES) {
        positionComponents[entity].x = x;
        positionComponents[entity].y = y;
        hasPosition[entity] = true;
    }
}

PositionComponent* getPositionComponent(Entity entity) {
    if (entity < MAX_ENTITIES) {
        return &positionComponents[entity];
    }
    return NULL;
}

