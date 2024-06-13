#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../../Graphics/include/color.h"
#include "../../Spatial/include/transform.h"
#include "../../Spatial/include/point2d.h"

// Structure de données pour un triangle
typedef struct Triangle {
    Point2D* points[3]; // Les trois points du triangle
    Color* color; // Couleur du triangle
} Triangle;

// Fonction pour initialiser un triangle
Triangle* Triangle_Init(Point2D* point1, Point2D* point2, Point2D* point3, Color* color);


#endif // TRIANGLE_H