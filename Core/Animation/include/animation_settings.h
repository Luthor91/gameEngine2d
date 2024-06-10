#ifndef ANIMATION_SETTINGS_H
#define ANIMATION_SETTINGS_H


typedef struct AnimationSettings {
    int speed;                    // Vitesse de l'animation (délai entre les frames)
    int currentFrame;             // Frame actuelle de l'animation
    int max_frame;                // Nombre maximal de frames
    int lastFrameTime;            // Temps de la dernière frame
    int repeat;                   // Nombre de répétitions
} AnimationSettings;

#endif // ANIMATION_SETTINGS_H