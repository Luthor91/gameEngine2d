#ifndef ENTITY_H
#define ENTITY_H

typedef unsigned int Entity;
// Max entity on screen
#define MAX_ENTITIES 4096

#include <stdbool.h>
#include "../../Components/include/position_component.h"
#include "../../Components/include/velocity_component.h"
#include "../../Components/include/sprite_component.h"
#include "../../Components/include/input_component.h"
#include "../../Components/include/transform_component.h"
#include "../../Components/include/animation_component.h"
#include "../../Components/include/hitbox_component.h"
#include "../../Components/include/size_component.h"
#include "../../Components/include/tag_component.h"
#include "../../Components/include/data_component.h"

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
extern bool hasSize[MAX_ENTITIES];
extern bool hasTags[MAX_ENTITIES];
extern bool hasDatas[MAX_ENTITIES];

extern Entity player_entity;

// Générateur d'ID simple pour les entités
Entity createEntity();
Entity createEntityWithId(int id);
Entity copyEntity(Entity entity);

Entity getEntity(int id);
Entity getFirstValidEntity();
Entity getFirstEmptyEntity();

void disableComponentEntity(Entity entity);

void disableComponentEntitiesFromRange(int start, int end);
void deactivateEntity(Entity entity);
void activateEntity(Entity entity);
void destroyEntity(Entity entity);
int getEntityCount();

bool isEntityValid(Entity entity);
bool isEntityEnabled(Entity entity);
bool hasPositionComponent(Entity entity);
bool hasVelocityComponent(Entity entity);
bool hasSpriteComponent(Entity entity);
bool hasInputComponent(Entity entity);
bool hasTransformComponent(Entity entity);
bool hasAnimationComponent(Entity entity);
bool hasHitboxComponent(Entity entity);
bool hasSizeComponent(Entity entity);
bool hasTagComponent(Entity entity);
bool hasDataComponents(Entity entity);

#endif