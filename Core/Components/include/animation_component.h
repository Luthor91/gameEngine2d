#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "../../Entities/include/entity.h"

typedef struct AnimationComponent {
    int currentFrame;
    int totalFrames;
    int frameDuration; // Durée de chaque frame en millisecondes
    Uint32 lastFrameTime; // Temps depuis la dernière frame
} AnimationComponent;

// Tableau pour stocker les AnimationComponents pour chaque entité
static AnimationComponent animationComponents[MAX_ENTITIES];

AnimationComponent* getAnimationComponent(Entity entity);
void addAnimationComponent(Entity entity, AnimationComponent animation);

#endif
