#ifndef EFFECT_H
#define EFFECT_H

#include "../../../Core/core.h"
#include "global.h"

void summonSecondBullet(Entity bullet, float directionX, float directionY, float coeff_passive);
void summonTrap(PositionComponent deathPosition);
void killChance();
void summonBarrel();
void explodeBarrel(Entity barrel);
void summonPoison();
void adjustEnemyDirection(Entity enemy, PositionComponent baitPosition);

#endif