#ifndef EVENT_H
#define EVENT_H

#include "../../../Core/core.h"
#include "global.h"

void onClick(Event event);
void onMove(Event event);
void onBullet_CollideWith_Enemy(Event event);
void onBullet_CollideWith_Barrel(Event event);
void onEnemy_CollideWith_Player(Event event);
void onTrap_CollideWith_Enemy(Event event);
void onDeath(Event event);
void onLeveling_Up(Event event);

#endif