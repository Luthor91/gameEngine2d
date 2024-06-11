#include "../include/transform.h"

Transform* Transform_Init(Point2D* pos, Size2D* size, const Point2D* center, double angle, double scale) {
    Transform* transform = (Transform*)malloc(sizeof(Transform));
    if (!transform) {
        printf("Transform_Init: Erreur d'allocation de mémoire pour Transform\n");
        return NULL;
    }

    if (scale <= 0) {
        scale = 1.0;
    }

    if (!pos || pos->x < 0 || pos->y < 0) {
        printf("Transform_Init: Erreur position invalide\n");
        free(transform);
        return NULL;
    }

    transform->position = (Point2D*)malloc(sizeof(Point2D));
    if (!transform->position) {
        printf("Transform_Init: Erreur d'allocation de mémoire pour position\n");
        free(transform);
        return NULL;
    }
    *(transform->position) = *pos;

    if (!size || size->height <= 0 || size->width <= 0) {
        printf("Transform_Init: Erreur taille invalide\n");
        free(transform->position);
        free(transform);
        return NULL;
    }

    transform->size = (Size2D*)malloc(sizeof(Size2D));
    if (!transform->size) {
        printf("Transform_Init: Erreur d'allocation de mémoire pour taille\n");
        free(transform->position);
        free(transform);
        return NULL;
    }
    *(transform->size) = *size;

    if (!center) {
        printf("Transform_Init: Erreur center invalide\n");
        free(transform->position);
        free(transform->size);
        free(transform);
        return NULL;
    }

    transform->center = (Point2D*)malloc(sizeof(Point2D));
    if (!transform->center) {
        printf("Transform_Init: Erreur d'allocation de mémoire pour center\n");
        free(transform->position);
        free(transform->size);
        free(transform);
        return NULL;
    }
    *(transform->center) = *center;

    transform->angle = angle;
    transform->scale = scale;

    return transform;
}