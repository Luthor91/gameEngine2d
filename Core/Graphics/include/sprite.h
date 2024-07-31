#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include "../../Spatial/include/transform.h"
#include "../../Graphics/include/texture.h"
#include "../../Utilities/include/string.h"
#include "../../Utilities/include/global.h"



/**
 * Représente un sprite, qui est une image affichée à l'écran avec une position et une taille spécifiques.
 */
typedef struct Sprite {
    int id; ///< Identifiant unique du sprite.
    Texture* texture; ///< Texture associée au sprite, contenant l'image à afficher.
    Transform* transform; ///< Transformations appliquées au sprite (position, taille, rotation, etc.).
} Sprite;

/**
 * Initialise un nouveau sprite.
 *
 * @param renderer Le renderer SDL2 utilisé pour dessiner le sprite.
 * @param transform La transformation à appliquer au sprite (position, taille, etc.).
 * @param texture La texture du sprite, contenant l'image à afficher.
 * @return Un pointeur vers le nouveau sprite initialisé, ou NULL en cas d'erreur.
 */
Sprite* Sprite_Init(Transform* transform, Texture* texture);

void Sprite_Set(Sprite* sprite, const char* params);

void Sprite_SetPosition(Sprite* sprite, int x, int y);

void Sprite_SetSize(Sprite* sprite, int width, int height);
/**
 * Détruit un sprite et libère ses ressources.
 *
 * @param sprite Le sprite à détruire.
 */
void Sprite_Destroy(Sprite* sprite);

#endif // SPRITE_H
