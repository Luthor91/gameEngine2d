#ifndef INIT_ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

#include "../../Globals/include/globals.h"
#include "../../Systems/include/game_system.h"
#include "../../Utils/include/time_utils.h"

#define MAX_LINE_LENGTH 1024

int Init_All();
int Init_Dependancies();
int Init_entity_attributes();

#endif // INIT_ENGINE_H
