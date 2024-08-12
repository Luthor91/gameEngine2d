#include "../include/movement_system.h"

void updateMovement(float deltaTime) {
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
        if (hasPositionComponent(entity) && hasVelocityComponent(entity)) {
            PositionComponent* pos = getPositionComponent(entity);
            VelocityComponent* vel = getVelocityComponent(entity);
            pos->x += vel->velocityX * deltaTime;
            pos->y += vel->velocityY * deltaTime;
        }
    }
}
