#include "../../Physics/include/acceleration.h"
#include <stdlib.h>

Acceleration* Acceleration_Init(float x, float y) {
    Acceleration* acceleration = (Acceleration*)malloc(sizeof(Acceleration));
    if (acceleration == NULL) return NULL;
    acceleration->x = x;
    acceleration->y = y;
    return acceleration;
}

void Acceleration_Destroy(Acceleration* acceleration) {
    free(acceleration);
}
