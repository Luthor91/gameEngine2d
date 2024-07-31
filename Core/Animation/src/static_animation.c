#include "../include/static_animation.h"

StaticAnimationManager* StaticAnimationManager_Init(int max_animation) {
    StaticAnimationManager* manager = (StaticAnimationManager*)malloc(sizeof(StaticAnimationManager));
    if (manager) {
        manager->static_animations = (StaticAnimation**)malloc(sizeof(StaticAnimation*) * max_animation);
        manager->max_animation = max_animation;
        manager->index = 0;
    }
    return manager;
}

void StaticAnimationManager_Add(StaticAnimationManager* manager, StaticAnimation* static_animation) {
    if (manager->index < manager->max_animation) {
        manager->static_animations[manager->index++] = static_animation;
    }
}

void StaticAnimationManager_Remove(StaticAnimationManager* manager, int index) {
    if (index < 0 || index >= manager->index) {
        return;
    }
    StaticAnimation_Destroy(manager->static_animations[index]);
    for (int i = index; i < manager->index - 1; i++) {
        manager->static_animations[i] = manager->static_animations[i + 1];
    }
    manager->index--;
}

StaticAnimation* StaticAnimation_Init(AnimationFrame** frames, AnimationSettings* animation_settings) {
    StaticAnimation* static_animation = (StaticAnimation*)malloc(sizeof(StaticAnimation));
    if (static_animation) {
        static_animation->frames = frames;
        static_animation->animation_settings = animation_settings;
    } else {
        fprintf(stderr, "StaticAnimation_Init: Échec de l'allocation mémoire\n");
    }
    return static_animation;
}

void StaticAnimation_Destroy(StaticAnimation* static_animation) {
    if (static_animation) {
        if (static_animation->frames) {
            free(static_animation->frames);
        }
        if (static_animation->animation_settings) {
            free(static_animation->animation_settings);
        }
        free(static_animation);
    }
}
