#ifndef GRID_H
#define GRID_H

#include "gridcell.h"

typedef struct Grid {
    int rows;
    int columns;
    int number_cells;
    Cell** cells;
} Grid;

Grid* Grid_Init(int rows, int columns);
void Grid_Generate(Grid* grid);
void Grid_Render(Grid* grid, SDL_Renderer* renderer);

Cell* Grid_GetCell(Grid* grid, int id);

#endif // GRID_H