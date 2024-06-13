#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "../../UI/include/window.h"

#define MAX_LINE_LENGTH 1024

void Init_Env(const char *filename);
int Init_All();
void Exit_All(Window* window);

#endif // INIT_H
