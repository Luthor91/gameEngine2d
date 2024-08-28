#ifndef CLEANUP_SYSTEM_H
#define CLEANUP_SYSTEM_H

#include "../../Entities/include/entity.h"
#include "../../Components/include/position_component.h"
#include "../../Utils/include/window_utils.h"
#include <stdbool.h>

#define MAX_CLEANUP_FUNCTIONS 128

typedef void (*CleanupFunction)(void);

void registerCleanupFunction(CleanupFunction func);
void cleanupSystem(void);

void addEntityToOutOfBoundsCleanup(Entity entity);
void cleanupOutOfBoundsEntities(void);

#endif // CLEANUP_SYSTEM_H