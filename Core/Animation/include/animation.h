#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdbool.h>
#include "../../Spatial/include/transform.h"
#include "../../Graphics/include/texture.h"
#include "../../Tilemap/include/tilemap.h"

/**
 * Structure représentant les paramètres d'une animation.
 *
 * @param speed Vitesse de l'animation, indiquant le délai entre les frames.
 * @param current_frame Frame actuelle de l'animation.
 * @param max_frame Nombre maximal de frames dans l'animation.
 * @param progress Progression de l'animation en pourcentage.
 * @param last_frame_time Temps écoulé depuis la dernière mise à jour de la frame.
 * @param start_time Temps de début de l'animation.
 * @param repeat Nombre de répétitions de l'animation (0 pour une seule fois, 1 pour ne pas se répéter, 2 pour reboucler, etc.).
 * @param is_playing Indicateur booléen indiquant si l'animation est en cours de lecture.
 */
typedef struct AnimationSettings {
    int speed;              ///< Vitesse de l'animation, délai entre les frames.
    int current_frame;     ///< Frame actuelle de l'animation.
    int max_frame;         ///< Nombre maximal de frames dans l'animation.
    float progress;        ///< Progression de l'animation en pourcentage.
    int last_frame_time;   ///< Temps écoulé depuis la dernière mise à jour de la frame.
    int start_time;        ///< Temps de début de l'animation.
    int repeat;            ///< Nombre de répétitions de l'animation (0 pour une seule fois, 1 pour rester à la dernière frame, 2 pour reboucler, 3 pour une autre boucle, etc.).
    bool is_playing;       ///< Indicateur si l'animation est en cours de lecture.
} AnimationSettings;

/**
 * Structure représentant une frame d'une animation.
 *
 * @param id Indice de la frame dans l'animation.
 * @param texture Pointeur vers la texture associée à cette frame.
 * @param transform Pointeur vers les données spatiales pour l'affichage de cette frame.
 */
typedef struct AnimationFrame {
    int id;                ///< Indice de la frame dans l'animation.
    Texture* texture;     ///< Texture associée à la frame.
    Transform* transform; ///< Données spatiales pour l'affichage de la frame.
} AnimationFrame;

/**
 * Initialise une AnimationFrame.
 *
 * @param id Indice de la frame.
 * @param texture Pointeur vers la texture de la frame.
 * @param transform Pointeur vers les données spatiales pour la frame.
 * @return Un pointeur vers une AnimationFrame initialisée.
 */
AnimationFrame* AnimationFrame_Init(int id, Texture* texture, Transform* transform);

/**
 * Initialise les paramètres d'une animation.
 *
 * @param speed Vitesse de l'animation (délai entre les frames).
 * @param max_frame Nombre maximal de frames dans l'animation.
 * @param repeat Nombre de répétitions (0 pour une fois, 1 pour bloquer à la dernière frame, 2 pour reboucler, etc.).
 * @return Un pointeur vers les paramètres d'animation initialisés.
 */
AnimationSettings* AnimationSettings_Init(int speed, int max_frame, int repeat);

/**
 * Génère un tableau de frames d'animation à partir d'un Tilemap et d'un tableau de Transformations.
 *
 * @param tilemap Pointeur vers le Tilemap contenant les informations sur les tuiles.
 * @param transforms Tableau de pointeurs vers les transformations pour chaque frame.
 * @return Un tableau de pointeurs vers les AnimationFrames générées.
 */
AnimationFrame** AnimationFrames_GenerateWithTransform(Tilemap* tilemap, Transform** transforms);

#endif // ANIMATION_H
