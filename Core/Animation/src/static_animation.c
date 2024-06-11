#include "static_animation.h"
#include <stdlib.h>

/**
 * Initialise un gestionnaire d'animations statiques
 * 
 * @param max_animated_sprite Nombre maximum d'animations statiques
 * @return Pointeur vers le gestionnaire d'animations statiques initialisé
 */
StaticAnimationManager* StaticAnimationManager_Init(int max_animated_sprite) {
    StaticAnimationManager* manager = (StaticAnimationManager*)malloc(sizeof(StaticAnimationManager));
    if (manager) {
        manager->dynamic_animation = (StaticAnimation**)malloc(sizeof(StaticAnimation*) * max_animated_sprite);
        manager->max_animated_sprite = max_animated_sprite;
        manager->index = 0;
    }
    return manager;
}

/**
 * Ajoute une animation statique au gestionnaire
 * 
 * @param manager Pointeur vers le gestionnaire d'animations statiques
 * @param static_animation Pointeur vers l'animation statique à ajouter
 */
void StaticAnimationManager_Add(StaticAnimationManager* manager, StaticAnimation* static_animation) {
    if (manager->index < manager->max_animated_sprite) {
        manager->dynamic_animation[manager->index++] = static_animation;
    }
}

/**
 * Supprime une animation statique du gestionnaire
 * 
 * @param manager Pointeur vers le gestionnaire d'animations statiques
 * @param index Index de l'animation statique à supprimer
 */
void StaticAnimationManager_Remove(StaticAnimationManager* manager, int index) {
    if (index < 0 || index >= manager->index) {
        return;
    }
    StaticAnimation_Destroy(manager->dynamic_animation[index]);
    for (int i = index; i < manager->index - 1; i++) {
        manager->dynamic_animation[i] = manager->dynamic_animation[i + 1];
    }
    manager->index--;
}

/**
 * Initialise une animation statique
 * 
 * @return Pointeur vers l'animation statique initialisée
 */
StaticAnimation* StaticAnimation_Init() {
    StaticAnimation* static_animation = (StaticAnimation*)malloc(sizeof(StaticAnimation));
    if (static_animation) {
        static_animation->frames = NULL; // À initialiser avec les frames réelles
        static_animation->animation_settings = (AnimationSettings*)malloc(sizeof(AnimationSettings));
    }
    return static_animation;
}

/**
 * Détruit une animation statique
 * 
 * @param static_animation Pointeur vers l'animation statique à détruire
 */
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
