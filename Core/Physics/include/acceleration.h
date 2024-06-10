#ifndef ACCELERATION_H
#define ACCELERATION_H

typedef struct Acceleration {
    float x;
    float y;
} Acceleration;

Acceleration* Acceleration_Init(float x, float y);
void Acceleration_Destroy(Acceleration* acceleration);

#endif // ACCELERATION_H
