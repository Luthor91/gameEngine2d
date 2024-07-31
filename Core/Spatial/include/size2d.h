#ifndef SIZE2D_H
#define SIZE2D_H

#define DEFAULT_SIZE2D_WIDTH 32
#define DEFAULT_SIZE2D_HEIGHT 32

/**
 * @brief Structure représentant une taille en 2D.
 */
typedef struct Size2D {
    int width;  ///< Largeur de la taille en 2D.
    int height; ///< Hauteur de la taille en 2D.
} Size2D;

/**
 * @brief Initialise une nouvelle taille 2D avec les dimensions spécifiées.
 * 
 * @param width Largeur de la taille en 2D.
 * @param height Hauteur de la taille en 2D.
 * @return Un pointeur vers la nouvelle taille 2D, ou NULL en cas d'échec.
 */
Size2D* Size2D_Init(int width, int height);

/**
 * @brief Détruit une taille 2D et libère les ressources associées.
 * 
 * @param size2d Pointeur vers la taille 2D à détruire.
 */
void Size2D_Destroy(Size2D* size2d);

#endif // SIZE2D_H
