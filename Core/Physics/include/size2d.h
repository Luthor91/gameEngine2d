#ifndef SIZE2D_H
#define SIZE2D_H

typedef struct Size2D{
    float length;
    float width;
} Size2D;

Size2D* Size2D_Init(float length, float width);
void Size2D_Destroy(Size2D* size2d);

#endif // SIZE2D_H
