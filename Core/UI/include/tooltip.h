#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include "../../Graphics/include/texture.h"
#include "../../Spatial/include/transform.h"
#include "../../Spatial/include/vector2.h"
#include "../../Spatial/include/area2d.h"
#include "../../Font/include/font.h"
#include "../../Utilities/include/string.h"
#include "../../Utilities/include/global.h"
#include "../../Utilities/include/object.h"

/**
 * @brief Structure représentant une fenêtre.
 */
typedef struct Tooltip {
    Transform* transform;
    Texture* texture;
    Vector2* offset; // Offset entre la souris et la tooltip
    Area2D* hitbox;
    Font* font;
    char* text;
    int max_length; ///< Longueur maximale du texte.
    int is_visible; // Flag pour indiquer si la tooltip doit être affichée
} Tooltip;

/**
 * @brief Initialise une nouvelle fenêtre avec un titre, une transformation et un chemin d'image pour l'arrière-plan.
 * 
 * @param title Le titre de la fenêtre.
 * @param transform La transformation spatiale à appliquer à la fenêtre.
 * @param sprite_path Le chemin vers le fichier image à utiliser comme arrière-plan.
 * @return Un pointeur vers la fenêtre nouvellement créée, ou NULL en cas d'échec.
 */
Tooltip* Tooltip_Init(Transform* transform, Texture* texture, Area2D* hitbox, Font* font, const char* initial_text);

void Tooltip_Set(Tooltip* tooltip, const char* params);

/**
 * @brief Définit le texte du champ de saisie.
 * 
 * @param tooltip Le champ de saisie.
 * @param text Le texte à définir.
 */
void Tooltip_SetText(Tooltip* tooltip, const char* text);

/**
 * @brief Définit la taille du texte du champ de saisie.
 * 
 * @param tooltip Le champ de saisie.
 * @param size La nouvelle taille du texte.
 */
void Tooltip_SetTextSize(Tooltip* tooltip, int size);

/**
 * @brief Définit la couleur du texte de l'input.
 * 
 * @param tooltip L'input.
 * @param color La nouvelle couleur du texte.
 */
void Tooltip_SetTextColor(Tooltip* tooltip, Color color);

/**
 * @brief Définit la couleur du texte de l'input.
 * 
 * @param tooltip L'input.
 * @param x La nouvelle couleur du texte.
 * @param y La nouvelle couleur du texte.
 */
void Tooltip_SetPosition(Tooltip* tooltip, int x, int y);

void Tooltip_SetSize(Tooltip* tooltip, int width, int height);

/**
 * @brief Détruit la fenêtre et libère les ressources associées.
 * 
 * @param tooltip Pointeur vers la fenêtre à détruire.
 */
void Tooltip_Destroy(Tooltip* tooltip);

#endif // TOOLTIP_H
