#ifndef EVENT_H
#define EVENT_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../UI/include/input.h"
#include "../../UI/include/button.h"
#include "../../UI/include/widget.h"
#include "../../UI/include/tooltip.h"

void Event_InputField(void* object, SDL_Event* event);

void Event_Button_Clicked(void* object, SDL_Event* event);

void Event_Widget_Dragged(void* object, SDL_Event* event);

void Event_Tooltip_Hovered(void* object, SDL_Event* event);

#endif // EVENT_H
