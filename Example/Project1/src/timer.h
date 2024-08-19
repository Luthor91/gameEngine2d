#ifndef TIMER_H
#define TIMER_H

#include "../../../Core/core.h"
#include "global.h"

void uponReloading(Event event);
void uponInvincibilityFinished(Event event);
void uponIncreasingDifficulty(Event event);
void uponSpawningEnemies(Event event);
void uponDispawningTrap(Event event);

#endif