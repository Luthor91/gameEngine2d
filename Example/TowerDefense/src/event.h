#ifndef EVENT_H
#define EVENT_H

#include "../../../Core/core.h"
#include "global.h"

void onBullet_Shoot(Event event);
void onBait_Spawn(Event event);
void onMove(Event event);
void onBullet_CollideWith_Enemy(Event event);
void onBullet_CollideWith_Barrel(Event event);
void onEnemy_CollideWith_Player(Event event);
void onTrap_CollideWith_Enemy(Event event);
void onDeathPlayer(Event event);
void onDeathEnemy(Event event);
void onDamaged(Event event);
void onLeveling_Up(Event event);

#endif