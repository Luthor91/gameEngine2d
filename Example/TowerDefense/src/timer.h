#ifndef TIMER_H
#define TIMER_H

#include "../../../Core/core.h"
#include "global.h"

void uponReloading(Event event);
void uponInvincibilityFinished(Event event);
void uponIncreasingDifficulty(Event event);
void uponSpawnEnemies(Event event);
void uponDispawnTrap(Event event);
void uponSpawnBarrel(Event event);
void uponDispawnBarrel(Event event);

void uponSpawnPoison(Event event);
void uponApplyingPoisonTicks(Event event);

void uponDispawnBait(Event event);

#endif