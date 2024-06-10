#include "../include/vector2.h"
#include <stdlib.h>

Vector2* Vector2_Init(float x, float y) {
    Vector2* vector = (Vector2*)malloc(sizeof(Vector2));
    if (vector == NULL) return NULL;
    vector->x = x;
    vector->y = y;
    return vector;
}

void Vector2_Destroy(Vector2* vector) {
    free(vector);
}
