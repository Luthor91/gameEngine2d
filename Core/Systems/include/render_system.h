#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <SDL2/SDL.h>
#include "../../Entities/include/entity.h"
#include "../../Components/include/sprite_component.h"
#include "../../Components/include/transform_component.h"

void renderEntities(SDL_Renderer* renderer);

#endif