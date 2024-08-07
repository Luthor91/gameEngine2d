#include "../include/transform.h"

Transform* Transform_Init(Point2D* pos, Size2D* size, Point2D* center, double angle, double scale) {
    Transform* transform = (Transform*)malloc(sizeof(Transform));
    if (!transform) {
        printf("Transform_Init: Erreur d'allocation de mémoire pour Transform\n");
        return NULL;
    }

    if (scale <= 0) {
        scale = 1.0;
    }

    transform->position = (Point2D*)malloc(sizeof(Point2D));
    if (!transform->position) {
        printf("Transform_Init: Erreur d'allocation de mémoire pour position\n");
        free(transform);
        return NULL;
    }
    if (!pos || pos->x < 0 || pos->y < 0) {
        transform->position->x = 0.0f;
        transform->position->y = 0.0f;
    } else {
        transform->position->x = pos->x;
        transform->position->y = pos->y;
    }

    transform->size = (Size2D*)malloc(sizeof(Size2D));
    if (!transform->size) {
        printf("Transform_Init: Erreur d'allocation de mémoire pour size\n");
        free(transform->position);
        free(transform);
        return NULL;
    }

    if (size == NULL || size->height <= 0 || size->width <= 0) {
        transform->size = Size2D_Init(32, 32);
    } else {
        transform->size->width = size->width;
        transform->size->height = size->height;
    }
    
    transform->center = (Point2D*)malloc(sizeof(Point2D));
    if (!transform->center) {
        printf("Transform_Init: Erreur d'allocation de mémoire pour center\n");
        free(transform->size);
        free(transform->position);
        free(transform);
        return NULL;
    }
    if (!center) {
        transform->center->x = 0.0f;
        transform->center->y = 0.0f;
    } else {
        transform->center->x = center->x;
        transform->center->y = center->y;
    }

    transform->angle = angle;
    transform->scale = scale;

    return transform;
}
