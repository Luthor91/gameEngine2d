#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "../../Entities/include/entity.h"

#define POSITION_ZERO {0.0f, 0.0f}

typedef struct PositionComponent {
    float x, y;
} PositionComponent;

static PositionComponent positionComponents[MAX_ENTITIES];

void addPositionComponent(Entity entity, PositionComponent position);
PositionComponent* getPositionComponent(Entity entity);


#endif
