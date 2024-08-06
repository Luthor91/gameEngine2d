#include "../include/progressbar.h"
#include <stdlib.h>

ProgressBar* ProgressBar_Init(Transform* transform, Color* background_color, Color* foreground_color, Color* border_color, float max_value, float current_value, int border_thickness) {
    ProgressBar* progress_bar = (ProgressBar*)malloc(sizeof(ProgressBar));
    if (!progress_bar) return NULL;

    progress_bar->transform = transform ? transform : Transform_Init(NULL, &(Size2D){DEFAULT_PROGRESSBAR_WIDTH, DEFAULT_PROGRESSBAR_HEIGHT}, NULL, 0, 0);
    progress_bar->max_value = max_value ? max_value : DEFAULT_MAX_VALUE;
    progress_bar->current_value = current_value ? current_value : 0;

    // Initialiser les couleurs
    progress_bar->background_color = background_color ? background_color : Color_Init(255, 255, 255, 255); // Blanc
    progress_bar->foreground_color = foreground_color ? foreground_color : Color_Init(0, 255, 0, 255); // Vert
    progress_bar->border_color = border_color ? border_color : Color_Init(0, 0, 0, 255); // Noir

    progress_bar->border_thickness = border_thickness ? border_thickness : DEFAULT_BORDER_THICKNESS;

    return progress_bar;
}

void ProgressBar_Set(ProgressBar* progress_bar, const char* params) {
    Object_Set(progress_bar, params, "ProgressBar");
}

void ProgressBar_SetValue(ProgressBar* progress_bar, float value) {
    if (!progress_bar) return;
    if (value < 0) value = 0;
    if (value > progress_bar->max_value) value = progress_bar->max_value;
    progress_bar->current_value = value;
}
