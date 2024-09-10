#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Globals/include/globals.h"
#include "Globals/include/constants.h"

#include "Entities/include/entity.h"

#include "Utils/include/init_utils.h"
#include "Utils/include/time_utils.h"
#include "Utils/include/window_utils.h"
#include "Utils/include/texture_utils.h"

#include "Components/include/position_component.h"
#include "Components/include/velocity_component.h"
#include "Components/include/sprite_component.h"
#include "Components/include/input_component.h"
#include "Components/include/hitbox_component.h"
#include "Components/include/size_component.h"
#include "Components/include/animation_component.h"
#include "Components/include/tag_component.h"
#include "Components/include/data_component.h"

#include "Systems/include/game_system.h"
#include "Systems/include/movement_system.h"
#include "Systems/include/input_system.h"
#include "Systems/include/event_system.h"
#include "Systems/include/render_system.h"
#include "Systems/include/animation_system.h"
#include "Systems/include/collision_system.h"
#include "Systems/include/timer_system.h"
#include "Systems/include/sound_system.h"
#include "Systems/include/particle_system.h"
#include "Systems/include/cleanup_system.h"

#endif
