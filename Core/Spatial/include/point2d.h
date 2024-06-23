#ifndef POINT2D_H
#define POINT2D_H

typedef struct Point2D {
    int x;
    int y;
} Point2D;

Point2D* Point2D_Init(int x, int y);
void Point2D_Destroy(Point2D* point);

#endif // POINT2D_H
