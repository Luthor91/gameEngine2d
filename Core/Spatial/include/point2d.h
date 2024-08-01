#ifndef POINT2D_H
#define POINT2D_H

/**
 * @brief Structure représentant un point en 2D.
 */
typedef struct Point2D {
    int x; ///< Coordonnée x du point.
    int y; ///< Coordonnée y du point.
} Point2D;

/**
 * @brief Initialise un nouveau point 2D avec les coordonnées spécifiées.
 * 
 * @param x Coordonnée x du point.
 * @param y Coordonnée y du point.
 * @return Un pointeur vers le nouveau point 2D, ou NULL en cas d'échec.
 */
Point2D* Point2D_Init(int x, int y);

Point2D* Point2D_Set(Point2D* point, int x, int y);

/**
 * @brief Détruit un point 2D et libère les ressources associées.
 * 
 * @param point Pointeur vers le point 2D à détruire.
 */
void Point2D_Destroy(Point2D* point);

#endif // POINT2D_H
