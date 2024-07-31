#include "../include/area2d.h"

Area2D* Area2D_Init(Point2D* position, Size2D* size) {
    if (position == NULL) {
        position = Point2D_Init(0, 0);
    }
    if (size == NULL) {
        size = Size2D_Init(0, 0);
    }
    
    Area2D* area = (Area2D*)malloc(sizeof(Area2D));
    area->position = position;
    area->size = size;

    return area;

}

void Area2D_Destroy(Area2D* area2d) {
    if (area2d != NULL) {
        Point2D_Destroy(area2d->position);
        Size2D_Destroy(area2d->size);
        free(area2d);
    }

}