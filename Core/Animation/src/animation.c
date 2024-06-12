#include "../include/animation.h"

/**
 * Initialise une frame d'animation
 * 
 * @param id Indice de la frame dans l'animation
 * @param texture Pointeur vers la texture de la frame
 * @param transform Pointeur vers les données spatiales de la frame
 * @return Pointeur vers l'AnimationFrame initialisée
 */
AnimationFrame* AnimationFrame_Init(int id, Texture* texture, Transform* transform) {
    AnimationFrame* frame = (AnimationFrame*)malloc(sizeof(AnimationFrame));
    if (frame) {
        frame->id = id;
        frame->texture = texture;
        frame->transform = transform;
    }
    return frame;
}

/**
 * Initialise une frame d'animation
 * 
 * @param speed Indique la vitesse de l'animation
 * @param max_frame indique le nombre maximum de frames de l'animation
 * @param repeat Booléen qui indique si l'animation doit se répeter
 * @return Pointeur vers l'AnimationFrame initialisée
 */
AnimationSettings* AnimationSettings_Init(int speed, int max_frame, bool repeat) {
    printf("AnimationSettings_Init: Initialisation de AnimationSettings\n");
    AnimationSettings* animation_settings = (AnimationSettings*)malloc(sizeof(AnimationSettings));
    if (animation_settings) {
        printf("AnimationSettings_Init: Allocation mémoire réussie\n");
        animation_settings->speed = speed;
        animation_settings->current_frame = 0;
        animation_settings->max_frame = max_frame;
        animation_settings->last_frame_time = 0;
        animation_settings->start_time = 0;
        animation_settings->repeat = repeat;

    } else {
        fprintf(stderr, "AnimationSettings_Init: Échec de l'allocation mémoire\n");
    }
    return animation_settings;
}
