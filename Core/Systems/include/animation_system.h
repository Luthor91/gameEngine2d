#ifndef ANIMATION_SYSTEM_H
#define ANIMATION_SYSTEM_H

#include "../../Entities/include/entity.h"
#include "../../Components/include/sprite_component.h"
#include "../../Components/include/animation_component.h"

int getTextureWidth(SDL_Texture* texture);
int getTextureHeight(SDL_Texture* texture);

void updateAnimations();

#endif
