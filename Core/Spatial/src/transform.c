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

    if (!pos || pos->x < 0 || pos->y < 0) {
        transform->position = Point2D_Init(0.0f, 0.0f);
    } else {
        transform->position = pos;
    }

    if (!size || size->height <= 0 || size->width <= 0) {
        transform->size = Size2D_Init(32, 32);
    } else {
        transform->size = size;
    }

    if (!center) {
        transform->center = Point2D_Init(0.0f, 0.0f);
    } else {
        transform->center = center;
    }

    transform->angle = angle;
    transform->scale = scale;

    return transform;
}


