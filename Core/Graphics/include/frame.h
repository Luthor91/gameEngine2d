#ifndef FRAME_H
#define FRAME_H

#include <SDL2/SDL.h>

typedef struct Frame {
    int id;
    SDL_Rect* bounds;
    SDL_Texture* texture;
} Frame;

Frame* Frame_Init(SDL_Rect* bounds, SDL_Texture* texture, int id);
void Frame_Render(Frame* frame, SDL_Renderer* renderer);

#endif // FRAME_H