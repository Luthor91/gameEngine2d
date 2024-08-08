#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include "../../Graphics/include/texture.h"
#include "../../Spatial/include/transform.h"
#include "../../Utilities/include/global.h"
#include "../../Utilities/include/object.h"

#define DEFAULT_WINDOW Window_Init(NULL, NULL, NULL)

/**
 * @brief Structure représentant une fenêtre.
 */
typedef struct Window {
    SDL_Window* sdl_window;  ///< Pointeur vers la fenêtre SDL.
    SDL_Renderer* renderer; ///< Pointeur vers le renderer SDL pour dessiner sur la fenêtre.
    Transform* transform;   ///< Transformation spatiale de la fenêtre.
    Texture* texture;       ///< Texture de fond pour la fenêtre.
} Window;

/**
 * @brief Initialise une nouvelle fenêtre avec un titre, une transformation et un chemin d'image pour l'arrière-plan.
 * 
 * @param title Le titre de la fenêtre.
 * @param transform La transformation spatiale à appliquer à la fenêtre.
 * @param sprite_path Le chemin vers le fichier image à utiliser comme arrière-plan.
 * @return Un pointeur vers la fenêtre nouvellement créée, ou NULL en cas d'échec.
 */
Window* Window_Init(char* title, Transform* transform, char* sprite_path);

void Window_Set(Window* window, const char* params);

/**
 * @brief Définit l'icône de la fenêtre à partir d'un fichier image.
 * 
 * @param window Pointeur vers la fenêtre pour laquelle définir l'icône.
 * @param filename Le chemin vers le fichier image de l'icône.
 * @return 0 en cas de succès, ou un code d'erreur en cas d'échec.
 */
int Window_SetIcon(Window* window, const char* filename);

/**
 * @brief Obtient les dimensions de la fenêtre.
 * 
 * @param window Pointeur vers la fenêtre dont obtenir les dimensions.
 * @return Pointeur vers une structure Size2D contenant la largeur et la hauteur de la fenêtre.
 */
Size2D* Window_GetSize(Window* window);

/**
 * @brief Détruit la fenêtre et libère les ressources associées.
 * 
 * @param window Pointeur vers la fenêtre à détruire.
 */
void Window_Destroy(Window* window);

#endif // WINDOW_H
