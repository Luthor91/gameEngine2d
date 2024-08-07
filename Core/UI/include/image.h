#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>

#include "../../Spatial/include/transform.h"
#include "../../Graphics/include/texture.h"
#include "../../Utilities/include/string.h"
#include "../../Utilities/include/global.h"
#include "../../Utilities/include/object.h"

/**
 * Représente un image, qui est une image affichée à l'écran avec une position et une taille spécifiques.
 */
typedef struct Image {
    int id; ///< Identifiant unique du image.
    Texture* texture; ///< Texture associée au image, contenant l'image à afficher.
    Transform* transform; ///< Transformations appliquées au image (position, taille, rotation, etc.).
} Image;

/**
 * Initialise un nouveau image.
 *
 * @param renderer Le renderer SDL2 utilisé pour dessiner le image.
 * @param transform La transformation à appliquer au image (position, taille, etc.).
 * @param texture La texture du image, contenant l'image à afficher.
 * @return Un pointeur vers le nouveau image initialisé, ou NULL en cas d'erreur.
 */
Image* Image_Init(Transform* transform, Texture* texture);

void Image_Set(Image* image, const char* params);

void Image_SetPosition(Image* image, int x, int y);

void Image_SetSize(Image* image, int width, int height);
/**
 * Détruit un image et libère ses ressources.
 *
 * @param image Le image à détruire.
 */
void Image_Destroy(Image* image);

#endif // IMAGE_H
