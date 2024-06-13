#ifndef POLYGON_H
#define POLYGON_H

#include "../../Graphics/include/color.h"
#include "../../Spatial/include/transform.h"
#include "../../Spatial/include/point2d.h"

// Structure de données pour une forme à X points
typedef struct Polygon {
    Point2D** points; // Tableau dynamique de points
    int num_points; // Nombre de points dans la forme
    Color* color; // Couleur de la forme
} Polygon;

// Fonction pour initialiser une forme à X points
Polygon* Polygon_Init(Point2D** points, int num_points, Color* color);

#endif // POLYGON_H