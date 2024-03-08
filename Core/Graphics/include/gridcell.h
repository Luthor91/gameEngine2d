#ifndef CELL_H
#define CELL_H

#include "sprite.h"

typedef struct Cell {
    int id;
    SDL_Rect* bounds;
    Sprite* sprite;
} Cell;

Cell* Cell_Init(SDL_Rect* bounds, int id);
void Cell_SetSprite(Cell* cell, Sprite* sprite);
void Cell_Render(Cell* cell, SDL_Renderer* renderer);

#endif // CELL_H