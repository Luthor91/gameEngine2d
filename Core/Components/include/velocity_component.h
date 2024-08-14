#ifndef VELOCITY_COMPONENT_H
#define VELOCITY_COMPONENT_H

#include "../../Entities/include/entity.h"

#define VELOCITY_ZERO {0, 0}

typedef struct VelocityComponent {
    float velocityX, velocityY;
} VelocityComponent;

void addVelocityComponent(Entity entity, VelocityComponent velocity);
VelocityComponent* getVelocityComponent(Entity entity);

#endif
