#ifndef VELOCITY_H
#define VELOCITY_H

typedef struct Velocity {
    float x;
    float y;
} Velocity;

Velocity* Velocity_Init(float x, float y);
void Velocity_Destroy(Velocity* velocity);

#endif // VELOCITY_H
