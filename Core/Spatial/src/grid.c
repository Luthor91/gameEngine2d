#include "../include/grid.h"

Cell* Cell_Init(int id, Point2D* position, Size2D* size) {
    Cell* cell = (Cell*)malloc(sizeof(Cell));
    if (cell) {
        cell->id = id;
        cell->position = position;
        cell->size = size;
    }
    return cell;
}

void Cell_Destroy(Cell* cell) {
    if (cell) {
        free(cell);
    }
}

Grid* Grid_Init(int rows, int columns, Size2D* tile_size) {
    Grid* grid = (Grid*)malloc(sizeof(Grid));
    if (grid) {
        grid->rows = rows;
        grid->columns = columns;
        grid->tile_size = tile_size;
        grid->number_cells = rows * columns;
        grid->cells = (Cell**)malloc(grid->number_cells * sizeof(Cell*));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                int id = i * columns + j;
                Point2D* position = (Point2D*)malloc(sizeof(Point2D));
                position->x = j * tile_size->width;
                position->y = i * tile_size->height;
                grid->cells[id] = Cell_Init(id, position, tile_size);
            }
        }
    }
    return grid;
}

void Grid_Destroy(Grid* grid) {
    if (grid) {
        for (int i = 0; i < grid->number_cells; ++i) {
            Cell_Destroy(grid->cells[i]);
        }
        free(grid->cells);
        free(grid);
    }
}

Cell* Grid_GetCellById(Grid* grid, int id) {
    if (id >= 0 && id < grid->number_cells) {
        return grid->cells[id];
    }
    return NULL;
}

Cell* Grid_GetCellByCoords(Grid* grid, Point2D* position) {
    int column = position->x / grid->tile_size->width;
    int row = position->y / grid->tile_size->height;

    if (column >= 0 && column < grid->columns && row >= 0 && row < grid->rows) {
        int id = row * grid->columns + column;
        return Grid_GetCellById(grid, id);
    }
    return NULL;
}
