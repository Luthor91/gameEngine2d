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

Cell* Cell_Init(SDL_Rect* bounds, int id) {
    
    Cell* cell = malloc(sizeof(Cell));

    if (bounds->w <= 0) {
        bounds->w = 1;
    }
    if (bounds->h <= 0) {
        bounds->h = 1;
    }

    cell->bounds = bounds;
    cell->id = id;

    return cell;

}

void Cell_SetSprite(Cell* cell, Sprite* sprite) {


    if(!cell->bounds) {
        printf("Cell_SetSprite: Erreur cell bounds inexistantes\n");
    }

    cell->sprite = sprite;
    cell->sprite->aspect->bounds = cell->bounds;

    return;

}

void Cell_Render(Cell* cell, SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, cell->sprite->texture, NULL, cell->bounds);
}