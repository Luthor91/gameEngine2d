#ifndef GRID_H
#define GRID_H

#include <stdlib.h>
#include "../../Spatial/include/point2d.h"
#include "../../Spatial/include/size2d.h"

/**
 * @brief Structure représentant une cellule dans une grille.
 */
typedef struct Cell {
    int id; ///< Identifiant unique de la cellule.
    Point2D* position; ///< Position de la cellule dans la grille.
    Size2D* size; ///< Taille de la cellule.
} Cell;

/**
 * @brief Structure représentant une grille de cellules.
 */
typedef struct Grid {
    Cell** cells; ///< Tableau de pointeurs vers les cellules dans la grille.
    Size2D* tile_size; ///< Taille des cellules dans la grille.
    int rows; ///< Nombre de lignes dans la grille.
    int columns; ///< Nombre de colonnes dans la grille.
    int number_cells; ///< Nombre total de cellules dans la grille.
} Grid;

/**
 * @brief Initialise une nouvelle grille avec les dimensions et la taille des cellules spécifiées.
 * 
 * @param rows Nombre de lignes dans la grille.
 * @param columns Nombre de colonnes dans la grille.
 * @param tile_size Pointeur vers une structure Size2D définissant la taille de chaque cellule.
 * @return Un pointeur vers la grille nouvellement créée, ou NULL en cas d'échec.
 */
Grid* Grid_Init(int rows, int columns, Size2D* tile_size);

/**
 * @brief Obtient une cellule de la grille par son identifiant.
 * 
 * @param grid Pointeur vers la grille.
 * @param id Identifiant de la cellule à récupérer.
 * @return Un pointeur vers la cellule correspondante, ou NULL si la cellule n'est pas trouvée.
 */
Cell* Grid_GetCellById(Grid* grid, int id);

/**
 * @brief Obtient une cellule de la grille par ses coordonnées.
 * 
 * @param grid Pointeur vers la grille.
 * @param position Pointeur vers une structure Point2D définissant les coordonnées de la cellule.
 * @return Un pointeur vers la cellule correspondante, ou NULL si la cellule n'est pas trouvée.
 */
Cell* Grid_GetCellByCoords(Grid* grid, Point2D* position);

/**
 * @brief Initialise une nouvelle cellule avec les paramètres spécifiés.
 * 
 * @param id Identifiant de la cellule.
 * @param position Pointeur vers une structure Point2D définissant la position de la cellule.
 * @param size Pointeur vers une structure Size2D définissant la taille de la cellule.
 * @return Un pointeur vers la cellule nouvellement créée, ou NULL en cas d'échec.
 */
Cell* Cell_Init(int id, Point2D* position, Size2D* size);

/**
 * @brief Détruit une grille et libère les ressources associées.
 * 
 * @param grid Pointeur vers la grille à détruire.
 */
void Grid_Destroy(Grid* grid);

/**
 * @brief Détruit une cellule et libère les ressources associées.
 * 
 * @param cell Pointeur vers la cellule à détruire.
 */
void Cell_Destroy(Cell* cell);

#endif // GRID_H
