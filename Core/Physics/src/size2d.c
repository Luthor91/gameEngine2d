#include "../include/size2d.h"
#include <stdlib.h>

Size2D* Size2D_Init(float length, float width) {
    Size2D* size = (Size2D*)malloc(sizeof(Size2D));
    if (size == NULL) return NULL;
    size->length = length;
    size->width = width;
    return size;
}

void Size2D_Destroy(Size2D* size) {
    free(size);
}
