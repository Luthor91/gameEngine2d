#ifndef STATIC_ANIMATION_H
#define STATIC_ANIMATION_H

#include "animation.h"

/**
 * Structure représentant une animation statique.
 *
 * @param frames Tableau de frames représentant l'animation.
 * @param animation_settings Pointeur vers les paramètres de l'animation (vitesse, répétition, etc.).
 */
typedef struct StaticAnimation {
    AnimationFrame** frames;             ///< Tableau de frames de l'animation statique.
    AnimationSettings* animation_settings; ///< Pointeur vers les paramètres de l'animation.
} StaticAnimation;

/**
 * Structure représentant un gestionnaire d'animations statiques.
 *
 * @param static_animations Tableau de pointeurs vers les animations statiques gérées.
 * @param max_animation Nombre maximal d'animations statiques que le gestionnaire peut contenir.
 * @param index Index actuel du gestionnaire pour suivre la position dans le tableau d'animations.
 */
typedef struct StaticAnimationManager {
    StaticAnimation** static_animations; ///< Tableau de pointeurs vers les animations statiques.
    int max_animation;                   ///< Nombre maximal d'animations statiques dans le gestionnaire.
    int index;                           ///< Index actuel du gestionnaire.
} StaticAnimationManager;

/**
 * Initialise un gestionnaire d'animations statiques avec une capacité maximale donnée.
 *
 * @param max_animation Nombre maximal d'animations statiques que le gestionnaire peut contenir.
 * @return Un pointeur vers un gestionnaire d'animations statiques initialisé.
 */
StaticAnimationManager* StaticAnimationManager_Init(int max_animation);

/**
 * Ajoute une animation statique au gestionnaire.
 *
 * @param manager Pointeur vers le gestionnaire d'animations statiques.
 * @param static_animation Pointeur vers l'animation statique à ajouter.
 */
void StaticAnimationManager_Add(StaticAnimationManager* manager, StaticAnimation* static_animation);

/**
 * Supprime une animation statique du gestionnaire en fonction de l'index.
 *
 * @param manager Pointeur vers le gestionnaire d'animations statiques.
 * @param index Index de l'animation statique à supprimer.
 */
void StaticAnimationManager_Remove(StaticAnimationManager* manager, int index);

/**
 * Initialise une animation statique avec les frames et les paramètres donnés.
 *
 * @param frames Tableau de frames pour l'animation statique.
 * @param animation_settings Pointeur vers les paramètres de l'animation statique.
 * @return Un pointeur vers une animation statique initialisée.
 */
StaticAnimation* StaticAnimation_Init(AnimationFrame** frames, AnimationSettings* animation_settings);

/**
 * Détruit une animation statique et libère les ressources associées.
 *
 * @param static_animation Pointeur vers l'animation statique à détruire.
 */
void StaticAnimation_Destroy(StaticAnimation* static_animation);

#endif // STATIC_ANIMATION_H
