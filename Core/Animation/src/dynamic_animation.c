#include "../include/dynamic_animation.h"

DynamicAnimationManager* DynamicAnimationManager_Init(int max_animated_sprite) {
    DynamicAnimationManager* manager = (DynamicAnimationManager*)malloc(sizeof(DynamicAnimationManager));
    if (!manager) {
        return NULL; // Allocation échouée
    }

    manager->dynamic_animations = (DynamicAnimation**)malloc(sizeof(DynamicAnimation*) * max_animated_sprite);
    if (!manager->dynamic_animations) {
        free(manager);
        return NULL; // Allocation échouée
    }

    manager->max_animated_sprite = max_animated_sprite;
    manager->index = 0;
    return manager;
}

void DynamicAnimationManager_Add(DynamicAnimationManager* manager, DynamicAnimation* dynamic_animation) {
    if (manager->index < manager->max_animated_sprite) {
        manager->dynamic_animations[manager->index++] = dynamic_animation;
    }
}

DynamicAnimation* DynamicAnimation_Init(AnimationFrame** startFrames, AnimationFrame** endFrames, AnimationSettings* animation_settings) {
    DynamicAnimation* dynamic_animation = (DynamicAnimation*)malloc(sizeof(DynamicAnimation));
    if (!dynamic_animation) {
        return NULL; // Allocation échouée
    }

    dynamic_animation->startFrames = startFrames;
    dynamic_animation->endFrames = endFrames;
    dynamic_animation->animation_settings = animation_settings;
    return dynamic_animation;
}

void DynamicAnimation_Destroy(DynamicAnimation* dynamic_animation) {
    if (dynamic_animation) {
        free(dynamic_animation->startFrames);
        free(dynamic_animation->endFrames);
        free(dynamic_animation->animation_settings);
        free(dynamic_animation);
    }
}

void DynamicAnimationManager_Remove(DynamicAnimationManager* manager, int index) {
    if (index < 0 || index >= manager->index) {
        return; // Index invalide
    }

    DynamicAnimation_Destroy(manager->dynamic_animations[index]);

    // Décaler les animations pour combler le trou
    for (int i = index; i < manager->index - 1; i++) {
        manager->dynamic_animations[i] = manager->dynamic_animations[i + 1];
    }

    manager->index--;
}



