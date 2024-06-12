#ifndef DYNAMIC_ANIMATION_H
#define DYNAMIC_ANIMATION_H

#include "animation.h"
/**
 * Animation qui peut bouger dans l'espace, à chaque frame, 
 * l'animation prendra la frame de départ puis la frame d'arrivé en compte
 * En cours de rework ?
 * 
 * startFrames AnimationFrame** : Frame de départ de l'animation
 * endFrames AnimationFrame** : Frames d'arrivée de l'animation
 * animation_settings AnimationSettings* : Paramètres de l'animation
 */
typedef struct DynamicAnimation {
    AnimationFrame** startFrames;
    AnimationFrame** endFrames;
    AnimationSettings* animation_settings;
} DynamicAnimation;

/**
 * Animation qui peut bouger dans l'espace, à chaque frame, 
 * l'animation prendra la frame de départ puis la frame d'arrivé en compte
 * En cours de rework ?
 * 
 * dynamic_animation DynamicAnimation** : Frame de départ de l'animation
 * max_animated_sprite int : Frames d'arrivée de l'animation
 * index int : index de l'animation actuelle ?
 */
typedef struct DynamicAnimationManager {
    DynamicAnimation** dynamic_animations;
    int max_animated_sprite;
    int index;
} DynamicAnimationManager;

DynamicAnimationManager* DynamicAnimationManager_Init(int max_animated_sprite);
void DynamicAnimationManager_Add(DynamicAnimationManager* manager, DynamicAnimation* dynamic_animation);


DynamicAnimation* DynamicAnimation_Init(AnimationFrame** startFrames, AnimationFrame** endFrames, AnimationSettings* animation_settings);
void DynamicAnimation_Destroy(DynamicAnimation* dynamic_animation);


#endif // DYNAMIC_ANIMATION_H