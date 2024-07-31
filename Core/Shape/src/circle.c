#include "../include/circle.h"

Circle* Circle_Init(Point2D* center, int rayon, Color* color) {
    Circle* circle = (Circle*)malloc(sizeof(Circle));
    if (circle) {
        circle->center = center;
        circle->rayon = rayon;
        circle->color = color;
    }
    return circle;
}

void Circle_Render(SDL_Renderer* renderer, Circle* circle) {
    SDL_SetRenderDrawColor(renderer, circle->color->r, circle->color->g, circle->color->b, circle->color->a);

    int d, y, x;
    d = 3 - (2 * circle->rayon);
    x = 0;
    y = circle->rayon;

    while (y >= x) {
        SDL_RenderDrawPoint(renderer, circle->center->x + x, circle->center->y + y);
        SDL_RenderDrawPoint(renderer, circle->center->x + y, circle->center->y + x);
        SDL_RenderDrawPoint(renderer, circle->center->x - x, circle->center->y + y);
        SDL_RenderDrawPoint(renderer, circle->center->x - y, circle->center->y + x);
        SDL_RenderDrawPoint(renderer, circle->center->x + x, circle->center->y - y);
        SDL_RenderDrawPoint(renderer, circle->center->x + y, circle->center->y - x);
        SDL_RenderDrawPoint(renderer, circle->center->x - x, circle->center->y - y);
        SDL_RenderDrawPoint(renderer, circle->center->x - y, circle->center->y - x);

        if (d < 0)
            d = d + (4 * x) + 6;
        else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}