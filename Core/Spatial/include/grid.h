#ifndef GRID_H
#define GRID_H

#include <stdlib.h>
#include "../../Spatial/include/point2d.h"
#include "../../Spatial/include/size2d.h"

typedef struct Cell {
    int id;
    Point2D* position;
    Size2D* size;
} Cell;

typedef struct Grid {
    Cell** cells;
    Size2D* tile_size;
    int rows;
    int columns;
    int number_cells;
} Grid;

Grid* Grid_Init(int rows, int columns, Size2D* tile_size);
Cell* Grid_GetCellById(Grid* grid, int id);
Cell* Grid_GetCellByCoords(Grid* grid, Point2D* position);

Cell* Cell_Init(int id, Point2D* position, Size2D* size);
void Grid_Destroy(Grid* grid);
void Cell_Destroy(Cell* cell);

#endif // GRID_H
