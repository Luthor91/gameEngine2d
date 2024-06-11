#ifndef SIZE2D_H
#define SIZE2D_H

typedef struct Size2D{
    float width;
    float height;
} Size2D;

Size2D* Size2D_Init(float width, float height);
void Size2D_Destroy(Size2D* size2d);

#endif // SIZE2D_H
