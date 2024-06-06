#include "../../Physics/include/force.h"
#include <stdlib.h>

Force* Force_Init(float x, float y) {
    Force* force = (Force*)malloc(sizeof(Force));
    if (force == NULL) {
        return NULL;
    }
    force->x = x;
    force->y = y;
    return force;
}

void Force_Destroy(Force* force) {
    free(force);
}