#include "../include/animation_component.h"

// Fonction pour obtenir un AnimationComponent pour une entité
AnimationComponent* getAnimationComponent(Entity entity) {
    if (entity < MAX_ENTITIES) {
        return &animationComponents[entity];
    }
    return NULL;
}

// Fonction pour ajouter un AnimationComponent à une entité
void addAnimationComponent(Entity entity, AnimationComponent animation) {
    if (entity < MAX_ENTITIES) {
        animationComponents[entity] = animation;
    }
}
