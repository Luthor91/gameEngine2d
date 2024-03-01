#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct Label {
    SDL_Renderer* renderer;
    SDL_Surface* surface;
    SDL_Color* color;
    
    SDL_Rect rect;
    SDL_Point center;
    double angle;
    double scale;
} Label;

#include "../include/label.h"

/**************************
    Initialisation du label
***************************/
Label* Label_Create(SDL_Renderer* renderer, const char* filepath);

Label* Label_Init(SDL_Renderer* renderer, int pos_x, int pos_y, int width, int height, int center_x, int center_y, double scale, double angle);
void Label_SetRectangle(Label* label, SDL_Rect rect);

void Label_SetScale(Label* label, double scale);

void Label_SetPosition(Label* label, int x, int y);

void Label_SetCenter(Label* label, int x, int y);

void Label_SetSize(Label* label, int width, int height);

void Label_SetRenderer(Label* label, SDL_Renderer* renderer);

void Label_UpdateCenter(Label* label);

void Label_UpdateRect(Label* label);

void Label_RenderStatic(Label* label, SDL_Renderer* renderer);
void Label_RenderTransformable(Label* label, SDL_Renderer* renderer, SDL_RendererFlip flip);
void Labels_RenderStatic(Label** labels, int numLabels, SDL_Renderer* renderer);
void Labels_RenderTransformable(Label** labels, int numLabels, SDL_Renderer* renderer, SDL_RendererFlip flip );

void Label_Destroy(Label* label);

#endif