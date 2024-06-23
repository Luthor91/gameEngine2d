#ifndef SIZE2D_H
#define SIZE2D_H

typedef struct Size2D{
    int width;
    int height;
} Size2D;

Size2D* Size2D_Init(int width, int height);
void Size2D_Destroy(Size2D* size2d);

#endif // SIZE2D_H
