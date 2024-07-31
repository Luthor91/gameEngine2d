#ifndef DYNAMIC_ANIMATION_H
#define DYNAMIC_ANIMATION_H

#include "animation.h"

/**
 * Structure représentant une animation dynamique qui peut bouger dans l'espace.
 * À chaque frame, l'animation utilise les frames de départ et d'arrivée spécifiées.
 *
 * @param startFrames Tableau de frames représentant le début de l'animation.
 * @param endFrames Tableau de frames représentant la fin de l'animation.
 * @param animation_settings Pointeur vers les paramètres de l'animation (vitesse, répétition, etc.).
 */
typedef struct DynamicAnimation {
    AnimationFrame** startFrames;        ///< Tableau de frames de départ de l'animation.
    AnimationFrame** endFrames;          ///< Tableau de frames d'arrivée de l'animation.
    AnimationSettings* animation_settings; ///< Pointeur vers les paramètres de l'animation.
} DynamicAnimation;

/**
 * Structure représentant un gestionnaire d'animations dynamiques.
 *
 * @param dynamic_animations Tableau de pointeurs vers les animations dynamiques gérées.
 * @param max_animated_sprite Nombre maximal d'animations dynamiques que le gestionnaire peut contenir.
 * @param index Index actuel du gestionnaire pour suivre la position dans le tableau d'animations.
 */
typedef struct DynamicAnimationManager {
    DynamicAnimation** dynamic_animations; ///< Tableau de pointeurs vers les animations dynamiques.
    int max_animated_sprite;               ///< Nombre maximal d'animations dynamiques dans le gestionnaire.
    int index;                            ///< Index actuel du gestionnaire.
} DynamicAnimationManager;

/**
 * Initialise un gestionnaire d'animations dynamiques avec une capacité maximale donnée.
 *
 * @param max_animated_sprite Nombre maximal d'animations dynamiques que le gestionnaire peut contenir.
 * @return Un pointeur vers un gestionnaire d'animations dynamiques initialisé.
 */
DynamicAnimationManager* DynamicAnimationManager_Init(int max_animated_sprite);

/**
 * Ajoute une animation dynamique au gestionnaire.
 *
 * @param manager Pointeur vers le gestionnaire d'animations dynamiques.
 * @param dynamic_animation Pointeur vers l'animation dynamique à ajouter.
 */
void DynamicAnimationManager_Add(DynamicAnimationManager* manager, DynamicAnimation* dynamic_animation);

/**
 * Initialise une animation dynamique avec les frames de départ et d'arrivée et les paramètres donnés.
 *
 * @param startFrames Tableau de frames de départ pour l'animation dynamique.
 * @param endFrames Tableau de frames de fin pour l'animation dynamique.
 * @param animation_settings Pointeur vers les paramètres de l'animation dynamique.
 * @return Un pointeur vers une animation dynamique initialisée.
 */
DynamicAnimation* DynamicAnimation_Init(AnimationFrame** startFrames, AnimationFrame** endFrames, AnimationSettings* animation_settings);

/**
 * Détruit une animation dynamique et libère les ressources associées.
 *
 * @param dynamic_animation Pointeur vers l'animation dynamique à détruire.
 */
void DynamicAnimation_Destroy(DynamicAnimation* dynamic_animation);

#endif // DYNAMIC_ANIMATION_H
