#include "../include/grid.h"

/**
 * Initialise une cellule
 * 
 * @param id Identifiant unique de la cellule
 * @param position Position de la cellule
 * @param size Taille de la cellule
 * @return Pointeur vers la cellule initialisée
 */
Cell* Cell_Init(int id, Point2D* position, Size2D* size) {
    Cell* cell = (Cell*)malloc(sizeof(Cell));
    if (cell) {
        cell->id = id;
        cell->position = position;
        cell->size = size;
    }
    return cell;
}

/**
 * Libère la mémoire allouée pour une cellule
 * 
 * @param cell Pointeur vers la cellule à libérer
 */
void Cell_Destroy(Cell* cell) {
    if (cell) {
        free(cell);
    }
}

/**
 * Initialise une grille
 * 
 * @param rows Nombre de lignes de la grille
 * @param columns Nombre de colonnes de la grille
 * @param tile_size Taille de chaque tuile
 * @return Pointeur vers la grille initialisée
 */
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

/**
 * Libère la mémoire allouée pour une grille et ses cellules
 * 
 * @param grid Pointeur vers la grille à libérer
 */
void Grid_Destroy(Grid* grid) {
    if (grid) {
        for (int i = 0; i < grid->number_cells; ++i) {
            Cell_Destroy(grid->cells[i]);
        }
        free(grid->cells);
        free(grid);
    }
}

/**
 * Récupère une cellule par son identifiant unique
 * 
 * @param grid Pointeur vers la grille
 * @param id Identifiant de la cellule à récupérer
 * @return Pointeur vers la cellule correspondante ou NULL si non trouvée
 */
Cell* Grid_GetCellById(Grid* grid, int id) {
    if (id >= 0 && id < grid->number_cells) {
        return grid->cells[id];
    }
    return NULL;
}

/**
 * Récupère une cellule par ses coordonnées dans la grille
 * 
 * @param grid Pointeur vers la grille
 * @param position Coordonnées de la cellule
 * @return Pointeur vers la cellule correspondante ou NULL si non trouvée
 */
Cell* Grid_GetCellByCoords(Grid* grid, Point2D* position) {
    int column = position->x / grid->tile_size->width;
    int row = position->y / grid->tile_size->height;

    if (column >= 0 && column < grid->columns && row >= 0 && row < grid->rows) {
        int id = row * grid->columns + column;
        return Grid_GetCellById(grid, id);
    }
    return NULL;
}
