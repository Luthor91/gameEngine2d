#ifndef EFFECT_H
#define EFFECT_H

#include "../../../Core/core.h"
#include "global.h"

void summonSecondBullet(Entity bullet, float directionX, float directionY, float coeff_passive);
void summonTrap(PositionComponent deathPosition);
void killChance();

#endif