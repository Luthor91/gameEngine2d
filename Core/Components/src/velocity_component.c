#include "../include/velocity_component.h"

static VelocityComponent velocityComponents[MAX_ENTITIES] = {0};

// Fonction pour ajouter un composant Sprite à une entité
void addVelocityComponent(Entity entity, VelocityComponent velocity) {
    if (entity < MAX_ENTITIES) {
        velocityComponents[entity] = velocity;
        hasVelocity[entity] = true;
    }
}

VelocityComponent* getVelocityComponent(Entity entity) {
    if (entity < MAX_ENTITIES && hasVelocity[entity]) {
        return &velocityComponents[entity];
    }
    return NULL;
}

