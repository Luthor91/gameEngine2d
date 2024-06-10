#ifndef ANIMATION_FRAME_H
#define ANIMATION_FRAME_H

#include <SDL2/SDL.h>

#include "../../Spatial/include/size2d.h"
#include "../../Spatial/include/point2d.h"
#include "../../Graphics/include/texture.h"

// 
typedef struct AnimationFrame {
    int id;
    Point2D* position;
    Point2D* center;
    Size2D* size;
    Texture* texture;
    double angle;
    double scale;
} AnimationFrame;

AnimatedFrame* Frame_Init(SDL_Rect* origin, SDL_Rect* target, SDL_Texture* texture, float delay, int id);
void Frame_SetOrigin(AnimatedFrame* frame, SDL_Rect* origin);
void Frame_Render(AnimatedFrame* frame, SDL_Renderer* renderer);
void Frame_Render_Debug(AnimatedFrame* frame, SDL_Renderer* renderer);

#endif // ANIMATION_FRAME_H