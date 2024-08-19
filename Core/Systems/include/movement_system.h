#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "../../Entities/include/entity.h"
#include "../../Components/include/position_component.h"
#include "../../Components/include/velocity_component.h"
#include "../../Components/include/hitbox_component.h"
#include "../../Components/include/tag_component.h"
#include "../../Utils/include/time.h"

void updateMovement(float deltaTime);

#endif