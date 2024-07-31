#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H

#include <SDL2/SDL.h>

#define MAX_RENDERER_CAPACITY 1024

/**
 * @brief Ajoute un renderer SDL au tableau global des renderers.
 * 
 * Cette fonction ajoute un nouvel objet SDL_Renderer au tableau global des renderers, 
 * permettant ainsi de gérer plusieurs fenêtres SDL avec leurs propres renderers.
 * 
 * @param renderer L'objet SDL_Renderer à ajouter.
 */
void SDL_Renderer_Add(SDL_Renderer* renderer);

/**
 * @brief Récupère un renderer SDL à partir du tableau global des renderers.
 * 
 * Cette fonction retourne un renderer SDL en fonction de l'index spécifié.
 * 
 * @param index L'index du renderer SDL à récupérer.
 * @return L'objet SDL_Renderer correspondant à l'index spécifié, ou NULL si l'index est invalide.
 */
SDL_Renderer* SDL_Renderer_Get(int index);

/**
 * @brief Récupère le renderer SDL courant.
 * 
 * Cette fonction retourne le renderer SDL qui est actuellement défini comme étant le renderer courant.
 * 
 * @return L'objet SDL_Renderer courant, ou NULL si aucun renderer n'est défini comme courant.
 */
SDL_Renderer* SDL_Renderer_Current();

#endif // SDL_RENDERER_H
