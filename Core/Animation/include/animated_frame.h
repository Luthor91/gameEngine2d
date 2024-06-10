#ifndef FRAME_H
#define FRAME_H

#include <SDL2/SDL.h>

typedef struct AnimatedFrame {
    int id;
    SDL_Rect* origin; // Position de la Frame dans le spritesheet
    SDL_Rect* target; // Position à l'écran
    SDL_Texture* texture;
    float delay;
} AnimatedFrame;

AnimatedFrame* Frame_Init(SDL_Rect* origin, SDL_Rect* target, SDL_Texture* texture, float delay, int id);
void Frame_SetOrigin(AnimatedFrame* frame, SDL_Rect* origin);
void Frame_Render(AnimatedFrame* frame, SDL_Renderer* renderer);
void Frame_Render_Debug(Frame* frame, SDL_Renderer* renderer);

#endif // FRAME_H