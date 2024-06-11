#ifndef POINT2D_H
#define POINT2D_H

typedef struct Point2D {
    float x;
    float y;
} Point2D;

Point2D* Point2D_Init(float x, float y);
void Point2D_Destroy(Point2D* point);

#endif // POINT2D_H
