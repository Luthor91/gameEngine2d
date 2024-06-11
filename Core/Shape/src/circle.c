#include "../include/circle.h"

// Fonction pour initialiser un cercle
Circle* Circle_Init(int cx, int cy, int rayon, Color color) {
    Circle* circle = (Circle*)malloc(sizeof(Circle));
    if (circle) {
        circle->cx = cx;
        circle->cy = cy;
        circle->rayon = rayon;
        circle->color = color;
    }
    return circle;
}

// Fonction pour dessiner un cercle
void Circle_Render(SDL_Renderer* renderer, Circle* circle) {
    SDL_SetRenderDrawColor(renderer, circle->color.r, circle->color.g, circle->color.b, circle->color.a);

    int d, y, x;
    d = 3 - (2 * circle->rayon);
    x = 0;
    y = circle->rayon;

    while (y >= x) {
        SDL_RenderDrawPoint(renderer, circle->cx + x, circle->cy + y);
        SDL_RenderDrawPoint(renderer, circle->cx + y, circle->cy + x);
        SDL_RenderDrawPoint(renderer, circle->cx - x, circle->cy + y);
        SDL_RenderDrawPoint(renderer, circle->cx - y, circle->cy + x);
        SDL_RenderDrawPoint(renderer, circle->cx + x, circle->cy - y);
        SDL_RenderDrawPoint(renderer, circle->cx + y, circle->cy - x);
        SDL_RenderDrawPoint(renderer, circle->cx - x, circle->cy - y);
        SDL_RenderDrawPoint(renderer, circle->cx - y, circle->cy - x);

        if (d < 0)
            d = d + (4 * x) + 6;
        else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}