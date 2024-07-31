#ifndef PANEL_H
#define PANEL_H

#include <stdlib.h>
#include "../../Graphics/include/texture.h"
#include "../../Spatial/include/transform.h"
#include "../../Utilities/include/string.h"
#include "../../Utilities/include/global.h"


/**
 * @brief Structure représentant un Panel.
 */
typedef struct Panel {
    Transform* transform; ///< La transformation spatiale du panneau.
    Texture* texture;     ///< La texture utilisée pour dessiner le panneau.
} Panel;

/**
 * @brief Initialise un nouveau panneau.
 * 
 * @param transform La transformation spatiale du panneau.
 * @param texture La texture utilisée pour dessiner le panneau.
 * @return Un pointeur vers le nouveau panneau initialisé.
 */
Panel* Panel_Init(Transform* transform, Texture* texture);

void Panel_Set(Panel* panel, const char* params);

void Panel_SetSize(Panel* panel, int width, int height);

void Panel_SetPosition(Panel* panel, int x, int y);

#endif // PANEL_H
