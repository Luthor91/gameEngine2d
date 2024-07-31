#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SDL2/SDL.h>

#include "size2d.h"
#include "point2d.h"

/**
 * @brief Structure représentant la transformation d'un objet.
 */
typedef struct Transform {
    Point2D* position;  ///< Position de l'objet dans l'espace.
    Size2D* size;       ///< Taille de l'objet.
    Point2D* center;    ///< Centre de l'objet pour la rotation et le redimensionnement.
    SDL_RendererFlip flip; ///< Flip (miroir) de l'objet lors du rendu.
    double angle;       ///< Angle de rotation de l'objet en degrés.
    double scale;       ///< Facteur de mise à l'échelle de l'objet.
} Transform;

/**
 * @brief Initialise une nouvelle transformation avec les paramètres spécifiés.
 * 
 * @param position Pointeur vers un `Point2D` représentant la position de l'objet.
 * @param size Pointeur vers un `Size2D` représentant la taille de l'objet.
 * @param center Pointeur vers un `Point2D` représentant le centre de l'objet.
 * @param angle Angle de rotation de l'objet en degrés.
 * @param scale Facteur de mise à l'échelle de l'objet.
 * @return Un pointeur vers la nouvelle instance de `Transform`, ou NULL en cas d'échec.
 */
Transform* Transform_Init(Point2D* position, Size2D* size, Point2D* center, double angle, double scale);

#endif // TRANSFORM_H
