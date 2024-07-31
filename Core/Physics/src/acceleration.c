#include "../../Physics/include/acceleration.h"
#include <stdlib.h>

Acceleration* Acceleration_Init(Vector2* accel) {
    Acceleration* acceleration = (Acceleration*)malloc(sizeof(Acceleration));
    if (acceleration == NULL) return NULL;
    acceleration->x = accel->x;
    acceleration->y = accel->y;
    return acceleration;
}

void Acceleration_Destroy(Acceleration* acceleration) {
    free(acceleration);
}
