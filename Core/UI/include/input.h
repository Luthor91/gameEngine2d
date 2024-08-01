#ifndef INPUT_H
#define INPUT_H

#include <stdlib.h>
#include "../../Spatial/include/transform.h"
#include "../../Graphics/include/texture.h"
#include "../../Font/include/font.h"
#include "../../Utilities/include/string.h"
#include "../../Utilities/include/global.h"
#include "../../Utilities/include/object.h"

/**
 * @brief Structure représentant un champ de saisie (InputField) graphique.
 */
typedef struct InputField {
    Texture* texture; ///< Texture de fond du champ de saisie.
    Transform* transform; ///< Contient le positionnement et la taille de l'objet.
    
    char* text; ///< Texte actuellement contenu dans le champ de saisie.
    Font* font; ///< Police, taille de police et couleur de la police utilisée.
    
    int max_length; ///< Longueur maximale du texte.
    int cursor_position; ///< Position du curseur dans le texte.
    int is_focused; ///< Indicateur si le champ de saisie est actuellement sélectionné (1 pour vrai, 0 pour faux).
} InputField;

/**
 * @brief Initialise un champ de saisie (InputField).
 * 
 * @param renderer Renderer SDL utilisé pour dessiner le champ de saisie.
 * @param font Police utilisée pour le texte du champ de saisie.
 * @param transform Transform représentant la position et la taille du champ de saisie.
 * @param max_length Longueur maximale du texte.
 * @param texture Texture de fond du champ de saisie (optionnelle).
 * @return Pointeur vers la structure InputField initialisée.
 */
InputField* InputField_Init(Transform* transform, Texture* texture, Font* font);

void InputField_Set(InputField* input_field, const char* params);

/**
 * @brief Définit le texte du champ de saisie.
 * 
 * @param input_field Le champ de saisie.
 * @param text Le texte à définir.
 */
void InputField_SetText(InputField* input_field, const char* text);

/**
 * @brief Définit la taille du texte du champ de saisie.
 * 
 * @param input_field Le champ de saisie.
 * @param size La nouvelle taille du texte.
 */
void InputField_SetTextSize(InputField* input_field, int size);

/**
 * @brief Définit la couleur du texte de l'input.
 * 
 * @param input_field L'input.
 * @param color La nouvelle couleur du texte.
 */
void InputField_SetTextColor(InputField* input_field, Color color);

void InputField_SetSize(InputField* input_field, int width, int height);

/**
 * @brief Définit la couleur du texte de l'input.
 * 
 * @param input_field L'input.
 * @param x La nouvelle couleur du texte.
 * @param y La nouvelle couleur du texte.
 */
void InputField_SetPosition(InputField* input_field, int x, int y);

#endif // INPUT_H