#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>

#include "../../Graphics/include/color.h"

// Structure de données pour un cercle
typedef struct Circle {
    Point2D* center; // Centre du cercle
    int rayon; // Rayon du cercle
    Color* color; // Couleur du cercle
} Circle;

// Fonction pour initialiser un cercle
Circle* Circle_Init(Point2D* center, int rayon, Color color);
// Fonction pour dessiner un cercle
void Circle_Render(SDL_Renderer* renderer, Circle* circle);

#endif // CIRCLE_H