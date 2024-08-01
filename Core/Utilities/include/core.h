#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../Utilities/include/global.h"
#include "../../Utilities/include/string.h"
#include "../../Utilities/include/init.h"
#include "../../Utilities/include/time.h"
#include "../../Utilities/include/object.h"

#include "../../Graphics/include/texture.h"
#include "../../Graphics/include/sprite.h"
#include "../../Graphics/include/spritesheet.h"
#include "../../Graphics/include/color.h"

#include "../../Renderer/include/renderer.h"
#include "../../Renderer/include/sdl_renderer.h"

#include "../../UI/include/button.h"
#include "../../UI/include/label.h"
#include "../../UI/include/window.h"
#include "../../UI/include/panel.h"
#include "../../UI/include/input.h"
#include "../../UI/include/widget.h"
#include "../../UI/include/tooltip.h"

#include "../../Events/include/timer_manager.h"
#include "../../Events/include/signal_manager.h"
#include "../../Events/include/event_manager.h"
#include "../../Events/include/event.h"

#include "../../Tilemap/include/tilemap.h"

#include "../../Shape/include/disc.h"
#include "../../Shape/include/polygon.h"
#include "../../Shape/include/triangle.h"
#include "../../Shape/include/circle.h"
#include "../../Shape/include/rectangle.h"

#include "../../Animation/include/static_animation.h"
#include "../../Animation/include/animation.h"
#include "../../Animation/include/dynamic_animation.h"

#include "../../Physics/include/physics.h"
#include "../../Physics/include/impulse.h"
#include "../../Physics/include/collision.h"
#include "../../Physics/include/material.h"
#include "../../Physics/include/velocity.h"
#include "../../Physics/include/characterbody.h"
#include "../../Physics/include/rigidbody.h"
#include "../../Physics/include/force.h"
#include "../../Physics/include/world_physics.h"
#include "../../Physics/include/staticbody.h"
#include "../../Physics/include/acceleration.h"

#include "../../Spatial/include/grid.h"
#include "../../Spatial/include/transform.h"
#include "../../Spatial/include/size2d.h"
#include "../../Spatial/include/point2d.h"
#include "../../Spatial/include/vector2.h"
#include "../../Spatial/include/area2d.h"

#include "../../Font/include/font.h"

int sdl_quit_flag = 0;

#endif
