#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <SDL2/SDL.h>
#include "../../Entities/include/entity.h"
#include "../../Systems/include/particle_system.h"
#include "../../Components/include/sprite_component.h"
#include "../../Components/include/transform_component.h"
#include "../../Utils/include/renderer_utils.h"

void renderEntities();

#endif
