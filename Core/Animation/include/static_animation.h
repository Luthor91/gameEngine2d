#ifndef STATIC_ANIMATION_H
#define STATIC_ANIMATION_H

#include "animation.h"

typedef struct StaticAnimation  {
    AnimationFrame** frames;
    AnimationSettings* animation_settings;
} StaticAnimation;

typedef struct StaticAnimationManager {
    StaticAnimation** static_animations;
    int max_animation;
    int index;
} StaticAnimationManager;

/**
 * Initialise un gestionnaire d'animations statiques
 * 
 * @param max_animation Nombre maximal de sprite dans l'animation
 * @return Pointeur vers le gestionnaire d'animations statiques initialisé
 */
StaticAnimationManager* StaticAnimationManager_Init(int max_animation);

/**
 * Ajoute une animation statique au gestionnaire
 * 
 * @param manager Pointeur vers le gestionnaire d'animations statiques
 * @param static_animation Pointeur vers l'animation statique à ajouter
 */
void StaticAnimationManager_Add(StaticAnimationManager* manager, StaticAnimation* static_animation);

/**
 * Supprime une animation statique du gestionnaire
 * 
 * @param manager Pointeur vers le gestionnaire d'animations statiques
 * @param index Index de l'animation statique à supprimer
 */
void StaticAnimationManager_Remove(StaticAnimationManager* manager, int index);

/**
 * Initialise une animation statique
 * 
 * @return Pointeur vers l'animation statique initialisée
 */
StaticAnimation* StaticAnimation_Init(AnimationFrame** frames, AnimationSettings* animation_settings);

/**
 * Détruit une animation statique
 * 
 * @param static_animation Pointeur vers l'animation statique à détruire
 */
void StaticAnimation_Destroy(StaticAnimation* static_animation);


#endif // STATIC_ANIMATION_H