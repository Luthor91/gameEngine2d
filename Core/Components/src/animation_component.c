#include "../include/animation_component.h"

static AnimationComponent animationComponents[MAX_ENTITIES];

// Fonction pour ajouter un AnimationComponent à une entité
void addAnimationComponent(Entity entity, AnimationComponent animation) {
    if (entity < MAX_ENTITIES) {
        animationComponents[entity] = animation;
        hasAnimation[entity] = true;
    }
}

// Fonction pour obtenir un AnimationComponent pour une entité
AnimationComponent* getAnimationComponent(Entity entity) {
    if (entity < MAX_ENTITIES && hasAnimation[entity]) {
        return &animationComponents[entity];
    }
    return NULL;
}

