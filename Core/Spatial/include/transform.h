#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SDL2/SDL.h>

#include "size2d.h"
#include "point2d.h"

typedef struct Transform {
    Point2D* position;
    Size2D* size;
    Point2D* center;
    SDL_RendererFlip flip;
    double angle;
    double scale;
} Transform;

Transform* Transform_Init(Point2D* position, Size2D* size, Point2D* center, double angle, double scale);

#endif // TRANSFORM_H