#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "../../Spatial/include/transform.h"
#include "../../Utilities/include/global.h"
#include "../../Utilities/include/object.h"


#define DEFAULT_BORDER_THICKNESS 1
#define DEFAULT_MAX_VALUE 100.0f

typedef struct {
    Transform* transform;       // Contient position et size
    float max_value;            // Valeur maximale de la progression
    float current_value;        // Valeur actuelle de la progression
    Color* background_color;    // Couleur de l'arrière-plan de la barre
    Color* foreground_color;    // Couleur de la partie remplie de la barre
    Color* border_color;        // Couleur de la bordure de la barre (optionnel)
    int border_thickness;       // Épaisseur de la bordure (optionnel)
} ProgressBar;

ProgressBar* ProgressBar_Init(Transform* transform, Color* background_color, Color* foreground_color, Color* border_color, float max_value, float current_value, int border_thickness);
void ProgressBar_Set(ProgressBar* progress_bar, const char* params);
void ProgressBar_SetValue(ProgressBar* progress_bar, float value);

#endif // PROGRESSBAR_H