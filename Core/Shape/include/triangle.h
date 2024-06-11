#ifndef TRIANGLE_H
#define TRIANGLE_H

// Structure de données pour un triangle
typedef struct Triangle {
    Point2D* points[3]; // Les trois points du triangle
    Color* color; // Couleur du triangle
} Triangle;

// Fonction pour initialiser un triangle
Triangle* Triangle_Init(Point2D* point1, Point2D* point2, Point2D* point3, Color* color);


#endif // TRIANGLE_H