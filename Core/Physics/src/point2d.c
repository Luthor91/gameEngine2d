#include "../include/point2d.h"
#include <stdlib.h>

Point2D* Point2D_Init(float x, float y) {
    Point2D* vector = (Point2D*)malloc(sizeof(Point2D));
    if (vector == NULL) return NULL;
    vector->x = x;
    vector->y = y;
    return vector;
}

void Point2D_Destroy(Point2D* vector) {
    free(vector);
}
