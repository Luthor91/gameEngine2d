#ifndef AREA2D_H
#define AREA2D_H

#define DEFAULT_AREA2D_WIDTH 32
#define DEFAULT_AREA2D_HEIGHT 32

#include <stdlib.h>
#include "point2d.h"
#include "size2d.h"

/**
 * @brief Structure représentant une taille en 2D.
 */
typedef struct Area2D {
    Point2D* position;
    Size2D* size;
} Area2D;

/**
 * @brief Initialise une nouvelle taille 2D avec les dimensions spécifiées.
 * 
 * @param position Largeur de la taille en 2D.
 * @param size Hauteur de la taille en 2D.
 * @return Un pointeur vers la nouvelle taille 2D, ou NULL en cas d'échec.
 */
Area2D* Area2D_Init(Point2D* position, Size2D* size);

/**
 * @brief Détruit une taille 2D et libère les ressources associées.
 * 
 * @param area2d Pointeur vers la taille 2D à détruire.
 */
void Area2D_Destroy(Area2D* area2d);

#endif // AREA2D_H
