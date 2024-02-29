#ifndef BUTTON_H
#define BUTTON_H

#include "sprite.h"

typedef struct Button {
    SDL_Rect rect;
    Sprite* sprite;
    int pressed;
    void (*on_click)(void*);
    void* data; 
} Button;

Button* Button_Create(int x, int y, int width, int height);
void Button_Destroy(Button* button);

int Button_SetPosition(Button* button, int x, int y);
int Button_SetSize(Button* button, int width, int height);
int Button_SetSprite(Button* button, SDL_Renderer* renderer, const char* path);

int Button_SyncRectWithSprite(Button* button);
int Button_SetOnClick(Button* button, void (*on_click)(void*), void* data);
int Button_IsPressed(Button* button, int x, int y);
void Button_Render(Button* button);

#endif