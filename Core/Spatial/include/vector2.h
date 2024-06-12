#ifndef VECTOR2_H
#define VECTOR2_H

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

Vector2* Vector2_Init(float x, float y);
void Vector2_Destroy(Vector2* vector);

#endif // VECTOR2_H
