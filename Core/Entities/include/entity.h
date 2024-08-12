#ifndef ENTITY_H
#define ENTITY_H

typedef unsigned int Entity;
#define MAX_ENTITIES 4096

#include <stdbool.h>
#include "../../Components/include/position_component.h"
#include "../../Components/include/velocity_component.h"
#include "../../Components/include/sprite_component.h"

// Tableau pour stocker les états des entités
static bool entityStates[MAX_ENTITIES] = { false };
static bool hasSprite[MAX_ENTITIES] = { false };
static bool hasPosition[MAX_ENTITIES] = { false };
static bool hasVelocity[MAX_ENTITIES] = { false };

// Générateur d'ID simple pour les entités
static Entity nextEntityID = 0;

Entity createEntity();
void destroyEntity(Entity entity);

bool hasPositionComponent(Entity entity);
bool hasVelocityComponent(Entity entity);
bool hasSpriteComponent(Entity entity);

#endif