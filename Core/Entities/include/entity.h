#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>
#include "../../Components/include/position_component.h"
#include "../../Components/include/velocity_component.h"
#include "../../Components/include/sprite_component.h"

#define MAX_ENTITIES 4096

typedef unsigned int Entity;

Entity createEntity();
void destroyEntity(Entity entity);

bool hasPositionComponent(Entity entity);
bool hasVelocityComponent(Entity entity);
bool hasSpriteComponent(Entity entity);

#endif