#include "../include/cleanup_system.h"
#include <stdio.h>

static CleanupFunction cleanupFunctions[MAX_CLEANUP_FUNCTIONS];
static int cleanupFunctionCount = 0;

static Entity outOfBoundsEntities[MAX_ENTITIES];
static int outOfBoundsEntityCount = 0;

void registerCleanupFunction(CleanupFunction func) {
    if (cleanupFunctionCount < MAX_CLEANUP_FUNCTIONS) {
        cleanupFunctions[cleanupFunctionCount++] = func;
    } else {
        printf("Warning: Maximum number of cleanup functions reached.\n");
    }
}

void cleanupSystem(void) {
    for (int i = 0; i < cleanupFunctionCount; ++i) {
        cleanupFunctions[i]();
    }
}

void addEntityToOutOfBoundsCleanup(Entity entity) {
    if (outOfBoundsEntityCount < MAX_ENTITIES) {
        outOfBoundsEntities[outOfBoundsEntityCount++] = entity;
    } else {
        printf("Warning: Maximum number of entities in out-of-bounds cleanup reached.\n");
    }
}

void removeEntityFromOutOfBoundsCleanup(int index) {
    if (index < 0 || index >= outOfBoundsEntityCount) {
        return;
    }
    // Décalage des entités pour combler le vide
    for (int i = index; i < outOfBoundsEntityCount - 1; ++i) {
        outOfBoundsEntities[i] = outOfBoundsEntities[i + 1];
    }
    --outOfBoundsEntityCount;
}

void cleanupOutOfBoundsEntities(void) {
    for (int i = 0; i < outOfBoundsEntityCount; ++i) {
        Entity entity = outOfBoundsEntities[i];

        if (!hasPositionComponent(entity)) continue;
        PositionComponent pos = *getPositionComponent(entity);

        if (pos.x < 0 || pos.x > game.window_width || pos.y < 0 || pos.y > game.window_height) {
            disableComponentEntity(entity);
            removeEntityFromOutOfBoundsCleanup(i);
            --i;
        }
    }
}