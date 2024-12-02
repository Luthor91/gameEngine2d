#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <SDL2/SDL.h>
#include "../../Globals/include/globals.h"
#include "../../Entities/include/entity.h"
#include "../../Systems/include/particle_system.h"
#include "../../Components/include/sprite_component.h"
#include "../../Components/include/transform_component.h"

SDL_Renderer* createRenderer(SDL_Window* window);
void renderEntities();
void renderEntitiesWithHitboxes();

#endif
