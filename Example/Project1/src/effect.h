#ifndef EFFECT_H
#define EFFECT_H

#include "../../../Core/core.h"
#include "global.h"

void amplify_bullet(Entity bullet);
void summonSecondBullet(Entity bullet, float direction_x, float direction_y);
void summonTrap(PositionComponent death_position);
void killChance();
void summonBarrel();
void explodeBarrel(Entity barrel);
void summonPoison();
void adjustEnemyDirection(Entity enemy, PositionComponent bait_position);

void handle_damage_received(Entity entity, float health);

#endif