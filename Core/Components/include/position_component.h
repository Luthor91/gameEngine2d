#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "../../Entities/include/entity.h"

typedef struct PositionComponent {
    float x, y;
} PositionComponent;

void addPositionComponent(Entity entity, float x, float y);
PositionComponent* getPositionComponent(Entity entity);

#endif
