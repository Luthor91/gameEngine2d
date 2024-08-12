#ifndef VELOCITY_COMPONENT_H
#define VELOCITY_COMPONENT_H

#include "../../Entities/include/entity.h"

typedef struct VelocityComponent {
    float velocityX, velocityY;
} VelocityComponent;

void addVelocityComponent(Entity entity, float x, float y);
VelocityComponent* getVelocityComponent(Entity entity);

#endif
