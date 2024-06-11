#include "../include/transform.h"

// Fonction d'initialisation pour la structure Transform
Transform* Transform_Init(Point2D* position, Size2D* size, const Point2D* center, double angle, double scale) {
    // Allocation de mémoire pour la structure Transform
    Transform* transform = (Transform*)malloc(sizeof(Transform));
    if (transform == NULL) {
        return NULL; // Retourner NULL en cas d'échec de l'allocation
    }

    // Allocation de mémoire et initialisation pour position
    transform->position = (Point2D*)malloc(sizeof(Point2D));
    if (transform->position == NULL) {
        free(transform);
        return NULL; // Retourner NULL en cas d'échec de l'allocation
    }
    transform->position->x = position->x;
    transform->position->y = position->y;

    // Allocation de mémoire et initialisation pour size
    transform->size = (Size2D*)malloc(sizeof(Size2D));
    if (transform->size == NULL) {
        free(transform->position);
        free(transform);
        return NULL; // Retourner NULL en cas d'échec de l'allocation
    }
    transform->size->width = size->width;
    transform->size->height = size->height;

    // Allocation de mémoire et initialisation pour center (optionnelle)
    if (center != NULL) {
        transform->center = (Point2D*)malloc(sizeof(Point2D));
        if (transform->center == NULL) {
            free(transform->size);
            free(transform->position);
            free(transform);
            return NULL; // Retourner NULL en cas d'échec de l'allocation
        }
        transform->center->x = center->x;
        transform->center->y = center->y;
    } else {
        transform->center = NULL;
    }

    // Initialisation de l'angle et de l'échelle
    transform->angle = angle;
    transform->scale = scale;

    return transform;
}