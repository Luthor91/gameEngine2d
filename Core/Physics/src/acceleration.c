#include "../../Physics/include/acceleration.h"
#include <stdlib.h>

Acceleration* Acceleration_Init(Vector2* accel) {
    Acceleration* acceleration = (Acceleration*)malloc(sizeof(Acceleration));
    acceleration = acceleration ? acceleration : (Acceleration*)Vector2_Init(0, 0);
    return acceleration;
}

void Acceleration_Destroy(Acceleration* acceleration) {
    free(acceleration);
}
