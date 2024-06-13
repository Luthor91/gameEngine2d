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
 * @param repeat 0: ne se répète pas; 1: répéter l'animation; 2: reboucler l'animation; 3: reboucler et répeter
 * @return Pointeur vers l'AnimationFrame initialisée
 */
AnimationSettings* AnimationSettings_Init(int speed, int max_frame, int repeat) {
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
        animation_settings->is_playing = true;

    } else {
        fprintf(stderr, "AnimationSettings_Init: Échec de l'allocation mémoire\n");
    }
    return animation_settings;
}

AnimationFrame** Generate_AnimationFramesWithTransform(Tilemap* tilemap, Transform** transforms) {
    int num_frames = tilemap->rows * tilemap->columns;
    AnimationFrame** frames = (AnimationFrame**)malloc(num_frames * sizeof(AnimationFrame*));
    if (!frames) {
        return NULL;
    }

    for (int i = 0; i < num_frames; i++) {
        Tile* tile = tilemap->tiles[i];
        AnimationFrame* frame = (AnimationFrame*)malloc(sizeof(AnimationFrame));
        frame->transform = transforms[i];
        frame->id = i;
        if (!frame) {
            // En cas d'échec, libérer la mémoire déjà allouée
            for (int j = 0; j < i; j++) {
                free(frames[j]);
            }
            free(frames);
            return NULL; // Échec de l'allocation mémoire
        }

        frame->texture = tile->texture;
        frame->transform->size = tile->size;

        frames[i] = frame;
    }

    return frames;
}
