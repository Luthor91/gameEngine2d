#ifndef ENTITY_H
#define ENTITY_H

typedef unsigned int Entity;
#define MAX_ENTITIES 4096

#include <stdbool.h>
#include "../../Components/include/position_component.h"
#include "../../Components/include/velocity_component.h"
#include "../../Components/include/sprite_component.h"
#include "../../Components/include/input_component.h"
#include "../../Components/include/transform_component.h"
#include "../../Components/include/animation_component.h"

#define INVALID_ENTITY_ID -1

// Tableau pour stocker les états des entités
extern bool entityStates[MAX_ENTITIES];
extern bool hasSprite[MAX_ENTITIES];
extern bool hasPosition[MAX_ENTITIES];
extern bool hasVelocity[MAX_ENTITIES];
extern bool hasInput[MAX_ENTITIES];
extern bool hasTransform[MAX_ENTITIES];
extern bool hasAnimation[MAX_ENTITIES];
extern bool hasHitbox[MAX_ENTITIES];
extern Entity playerEntity;

// Générateur d'ID simple pour les entités
static Entity nextEntityID = 0;
Entity createEntity();
Entity getEntity(int id);

void destroyEntity(Entity entity);

bool hasPositionComponent(Entity entity);
bool hasVelocityComponent(Entity entity);
bool hasSpriteComponent(Entity entity);
bool hasInputComponent(Entity entity);
bool hasTransformComponent(Entity entity);
bool hasAnimationComponent(Entity entity);

#endif