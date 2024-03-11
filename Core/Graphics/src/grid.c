#include "../include/grid.h"

Grid* Grid_Init(int rows, int columns) {
    
    Grid* grid = (Grid*)malloc(sizeof(Grid));

    if (rows <= 0) {
        rows = 1;
    }
    if (columns <= 0) {
        columns = 1;
    }

    grid->rows = rows;
    grid->columns = columns;
    grid->number_cells = rows * columns;
    grid->cells = (Cell**)malloc(grid->number_cells * sizeof(Cell*));

    return grid;

}

void Grid_Generate(Grid* grid) {
    
    int max_cells = grid->number_cells;
    int x = 0; int y = 0;

    for (int i = 0; i < max_cells; i++, x++) {

        if (i % grid->rows == 0 && i != 0) {
            x = 0;
            y++;
        }

        SDL_Rect* bounds = (SDL_Rect*)malloc(sizeof(SDL_Rect));
        bounds->x = x * 30;
        bounds->y = y * 30;
        bounds->h = 30;
        bounds->w = 30;
        grid->cells[i] = Cell_Init(bounds, i);

    }

    return;
}

void Grid_Render(Grid* grid, SDL_Renderer* renderer) {
    
    int max_cells = grid->number_cells;
    int i = 0;

    for (i = 0; i < max_cells; i++) {
        Cell_Render(grid->cells[i], renderer);
    }

    return;
}

Cell* Grid_GetCell(Grid* grid, int id) {

    while(id > grid->number_cells) {
        id -= (grid->number_cells-1);
    }
    while(id < 0) {
        id += grid->number_cells;
    }

    if(!grid->cells[id] || !grid->cells[id]->id) {
        return NULL;
    }

    return grid->cells[id];

}