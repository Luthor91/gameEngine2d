#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "../../Entities/include/entity.h"

#define ANIMATION_ZERO {0, 1, 0, 0, true}

typedef struct AnimationComponent {
    int currentFrame;
    int totalFrames;
    int frameDuration;
    Uint32 lastFrameTime;
    bool is_active;
} AnimationComponent;

AnimationComponent* getAnimationComponent(Entity entity);
void addAnimationComponent(Entity entity, AnimationComponent animation);

#endif
