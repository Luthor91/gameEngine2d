#ifndef GRID_H
#define GRID_H

#include "sprite.h"

typedef struct Grid {
    int rows;
    int columns;
    int number_cells;
    Cell** cells;
} Grid;

typedef struct Cell {
    int id;
    SDL_Rect* bounds;
    Sprite* sprite;
} Cell;

Grid* Grid_Init(int rows, int columns);
void Grid_Generate(Grid* grid);
void Grid_Render(Grid* grid, SDL_Renderer* renderer);
Cell* Grid_GetCell(Grid* grid, int id);

Cell* Cell_Init(SDL_Rect* bounds, int id);
void Cell_SetSprite(Cell* cell, Sprite* sprite);
void Cell_Render(Cell* cell, SDL_Renderer* renderer);

#endif // GRID_H