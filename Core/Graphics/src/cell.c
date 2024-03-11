#include "../include/cell.h"

Cell* Cell_Init(SDL_Rect* bounds, Sprite* sprite) {
    
    Cell* cell = malloc(sizeof(Cell));

    if (bounds->w <= 0) {
        bounds->w = 1;
    }
    if (bounds->h <= 0) {
        bounds->h = 1;
    }

    cell->bounds = bounds;

    return cell;

}

void Cell_SetSprite(Cell* cell, Sprite* sprite) {


    if(!cell->bounds) {
        printf("Cell_SetSprite: Erreur cell bounds inexistantes\n");
    }

    cell->sprite = sprite;
    cell->sprite->transform->bounds = cell->bounds;

    return;

}

void Cell_Render(Cell* cell, SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, cell->sprite->texture, NULL, cell->bounds);
}