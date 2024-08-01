#include "../include/point2d.h"
#include <stdlib.h>

Point2D* Point2D_Init(int x, int y) {
    Point2D* vector = (Point2D*)malloc(sizeof(Point2D));
    if (vector == NULL) return NULL;
    vector->x = x;
    vector->y = y;
    return vector;
}

Point2D* Point2D_Set(Point2D* point, int x, int y) {

    if (x < 0) {
        x = point->x;
    }

    if (y < 0) {
        y = point->y;
    }
    
    point->x = x;
    point->y = y;

    return point;

}

void Point2D_Destroy(Point2D* vector) {
    free(vector);
}
