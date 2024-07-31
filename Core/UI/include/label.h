#ifndef LABEL_H
#define LABEL_H

#include <stdint.h>
#include <ctype.h>

#include "../../Utilities/include/string.h"
#include "../../Spatial/include/transform.h"
#include "../../Font/include/font.h"
#include "../../Graphics/include/texture.h"
#include "../../Graphics/include/color.h"

#define DEFAULT_LABEL_WIDTH 128
#define DEFAULT_LABEL_HEIGHT 64
#define DEFAULT_MAX_LENGHT_LABEL 1024

/**
 * @brief Structure représentant un Label.
 */
typedef struct Label {
    Transform* transform; ///< La transformation spatiale du label.
    Texture* texture; ///< La transformation spatiale du label.
    Font* font;           ///< La police utilisée pour afficher le texte.
    char* text;           ///< Le texte affiché par le label.
    int max_length; ///< Longueur maximale du texte.
} Label;

/**
 * @brief Initialise un nouveau label.
 * 
 * @param transform La transformation spatiale du label.
 * @param font La police utilisée pour afficher le texte.
 * @param text Le texte affiché par le label.
 * @return Un pointeur vers le nouveau label initialisé.
 */
Label* Label_Init(Transform* transform, Texture* texture, Font* font, char* text) ;

void Label_Set(Label* label, const char* params);

/**
 * @brief Définit le texte du label.
 * 
 * @param label Le label.
 * @param text Le texte à définir.
 */
void Label_SetText(Label* label, const char* text);

/**
 * @brief Définit la taille du texte du label.
 * 
 * @param label Le label.
 * @param size La nouvelle taille du texte.
 */
void Label_SetTextSize(Label* label, int size);

/**
 * @brief Définit la couleur du texte du label.
 * 
 * @param label Le label.
 * @param color La nouvelle couleur du texte.
 */
void Label_SetTextColor(Label* label, Color color);

void Label_SetPosition(Label* label, int x, int y);

void Label_SetSize(Label* label, int width, int height);

#endif // LABEL_H
