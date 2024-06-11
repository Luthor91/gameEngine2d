#ifndef RECTANGLE_H
#define RECTANGLE_H

// Structure de données pour un rectangle
typedef struct Rectangle {
    Point2D* position; // Position du coin supérieur gauche du rectangle
    int width; // Largeur du rectangle
    int height; // Hauteur du rectangle
    Color* color; // Couleur du rectangle
} Rectangle;

// Fonction pour initialiser un rectangle
Rectangle* Rectangle_Init(Point2D* position, int width, int height, Color* color);


#endif // RECTANGLE_H