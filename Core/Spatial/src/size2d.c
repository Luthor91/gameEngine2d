#include "../include/size2d.h"
#include <stdlib.h>

Size2D* Size2D_Init(float width, float height) {
    Size2D* size = (Size2D*)malloc(sizeof(Size2D));
    if (size == NULL) return NULL;
    size->width = width;
    size->height = height;
    
    return size;
}

void Size2D_Destroy(Size2D* size) {
    free(size);
}
