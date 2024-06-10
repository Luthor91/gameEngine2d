#include "../include/velocity.h"
#include <stdlib.h>

Velocity* Velocity_Init(float x, float y) {
    Velocity* velocity = (Velocity*)malloc(sizeof(Velocity));
    if (velocity == NULL) return NULL;
    velocity->x = x;
    velocity->y = y;
    return velocity;
}

void Velocity_Destroy(Velocity* velocity) {
    free(velocity);
}
