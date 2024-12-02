#include "../include/movement_system.h"

void updateMovement(float deltaTime) {
    for (size_t i = 0; i < getEntityCount(); ++i) {
        Entity entity = getEntity(i);
        if (!hasPositionComponent(entity) || !hasVelocityComponent(entity)) continue;

        PositionComponent* pos = getPositionComponent(entity);
        VelocityComponent* vel = getVelocityComponent(entity);
        pos->x += vel->x * deltaTime;
        pos->y += vel->y * deltaTime;
    }
}
