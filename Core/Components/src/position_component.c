#include "../include/position_component.h"

static PositionComponent positionComponents[MAX_ENTITIES] = {0};

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

PositionComponent* getCenterPosition(Entity entity) {
    if (entity < MAX_ENTITIES && hasPosition[entity] && hasSize[entity]) {
        PositionComponent position = positionComponents[entity];
        SizeComponent* size = getSizeComponent(entity);
        
        // Allouer de la mémoire pour le centre
        PositionComponent* center = malloc(sizeof(PositionComponent));
        if (center != NULL) {
            // Initialiser les champs de la structure
            center->x = position.x + size->width / 2.0f;
            center->y = position.y + size->height / 2.0f;
        } else {
            return NULL;
        }
        return center;
    }
    return NULL;
}


