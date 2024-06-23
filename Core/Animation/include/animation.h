#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdbool.h>
#include "../../Spatial/include/transform.h"
#include "../../Graphics/include/texture.h"
#include "../../Tilemap/include/tilemap.h"

/**
 * Paramètres de l'animation, si elle est répétable, sa vitesse, la frame actuelle...
 * 
 * speed int : Vitesse de l'animation (délai entre les frames)
 * current_frame int : Frame actuelle de l'animation
 * max_frame int : Nombre maximal de frames
 * last_frame_time int : Temps de la dernière frame
 * start_time int : Temps de commencement de l'aniamtion
 * repeat int : Nombre de répétitions
 * is_playing bool; 
 */
typedef struct AnimationSettings {
    int speed;
    int current_frame;
    int max_frame;
    float progress;
    int last_frame_time;
    int start_time;
    int repeat;
    bool is_playing;
} AnimationSettings;

/**
 * Définition d'une frame d'une animation, contient des données d'affichage de la frame et la texture.
 * 
 * id int : indice de la Frame dans l'animation
 * texture Texture* : informations sur la texture source
 * transform Transform* : données spatiales pour l'affichage
 * 
 */
typedef struct AnimationFrame {
    int id;
    Texture* texture;
    Transform* transform;
} AnimationFrame;

AnimationFrame* AnimationFrame_Init(int id, Texture* texture, Transform* transform);

/** 
 * repeat = 0 animation normale
 * repeat = 1 animation se bloque a la dernière frame
 * repeat = 2 animation reboucle
 * repeat = 3 animation reboucle
 * 
 * */
AnimationSettings* AnimationSettings_Init(int speed, int max_frame, int repeat);


AnimationFrame** AnimationFrames_GenerateWithTransform(Tilemap* tilemap, Transform** transforms);
#endif // ANIMATION_H