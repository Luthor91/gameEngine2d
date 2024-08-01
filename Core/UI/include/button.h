#ifndef BUTTON_H
#define BUTTON_H

#include <stdlib.h>
#include "../../Spatial/include/transform.h"
#include "../../Graphics/include/texture.h"
#include "../../Utilities/include/string.h"
#include "../../Utilities/include/global.h"
#include "../../Utilities/include/object.h"

/**
 * @brief Structure représentant un bouton interactif.
 */
typedef struct Button {
    Transform* transform;   ///< La transformation spatiale du bouton.
    Texture* texture;       ///< La texture graphique du bouton.
    int pressed;            ///< Indicateur si le bouton est pressé.
    void (*on_click)(void*);///< Fonction callback à appeler lors d'un clic sur le bouton.
    void* data;             ///< Données supplémentaires passées à la fonction callback.
} Button;

/**
 * @brief Initialise un bouton avec les paramètres spécifiés.
 * 
 * @param aspect La transformation spatiale du bouton.
 * @param texture La texture graphique du bouton.
 * @param on_click La fonction callback à appeler lors d'un clic sur le bouton.
 * @param data Les données supplémentaires à passer à la fonction callback.
 * @return Button* Pointeur vers le bouton initialisé.
 */
Button* Button_Init(Transform* aspect, Texture* texture, void (*on_click)(void*), void* data);

void Button_Set(Button* button, const char* params);

/**
 * @brief Détruit un bouton et libère la mémoire associée.
 * 
 * @param button Le bouton à détruire.
 */
void Button_Destroy(Button* button);

/**
 * @brief Définit la fonction callback à appeler lors d'un clic sur le bouton.
 * 
 * @param button Le bouton à modifier.
 * @param on_click La nouvelle fonction callback à appeler lors d'un clic.
 * @param data Les nouvelles données supplémentaires à passer à la fonction callback.
 * @return int Retourne 0 en cas de succès, ou -1 en cas d'erreur.
 */
int Button_SetOnClick(Button* button, void (*on_click)(void*), void* data);

void Button_SetPosition(Button* button, int x, int y);

void Button_SetSize(Button* button, int width, int height);

#endif // BUTTON_H
