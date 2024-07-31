#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdarg.h>

#include "../../Animation/include/animation.h"
#include "../../Animation/include/dynamic_animation.h"
#include "../../Animation/include/static_animation.h"

#include "../../Graphics/include/texture.h"
#include "../../Graphics/include/sprite.h"

#include "../../UI/include/window.h"
#include "../../UI/include/label.h"
#include "../../UI/include/panel.h"
#include "../../UI/include/input.h"
#include "../../UI/include/button.h"
#include "../../UI/include/widget.h"
#include "../../UI/include/tooltip.h"

// Cette valeur représente le nombre maximum d'objets qui peuvent être rendus par le système.
// Cette limite est en cours de vérification, car des valeurs trop élevées peuvent entraîner des
// problèmes de segmentation (segfault) lors du tri des objets de rendu.
// La valeur est définie pour éviter les erreurs potentielles liées à la gestion de trop nombreux objets.
#define MAX_RENDERED_OBJECTS 1045000

// Cette valeur représente le nombre maximum de renderers (objets de rendu) que le `RendererManager`
// peut gérer. Elle est définie comme étant un de plus que `MAX_RENDERED_OBJECTS` pour inclure un
// espace supplémentaire, permettant ainsi d'éviter les dépassements de tableau ou les erreurs liées
// à une gestion incorrecte du nombre maximal d'objets de rendu.
#define DEFAULT_MAX_RENDERER (MAX_RENDERED_OBJECTS + 1)

/**
 * @brief Structure représentant un objet à rendre.
 */
typedef struct Renderer {
    void (*renderFunction)(struct Renderer*, SDL_Renderer*); ///< Fonction de rendu associée à l'objet.
    void* object; ///< Pointeur vers l'objet affichable.
    int z_index; ///< Index Z pour déterminer l'ordre de rendu.
} Renderer;

/**
 * @brief Structure de gestion des objets de rendu.
 */
typedef struct RendererManager {
    Renderer** renderers; ///< Tableau de pointeurs vers des objets `Renderer`.
    SDL_Renderer* sdl_renderer; ///< Pointeur vers le renderer SDL.
    int max_renderers; ///< Nombre maximum d'objets de rendu.
    int current_renderer_count; ///< Nombre actuel d'objets de rendu.
} RendererManager;

/**
 * @brief Initialise un `RendererManager` avec un renderer SDL et une capacité maximale.
 * 
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 * @param max_renderers Nombre maximum d'objets de rendu à gérer.
 * @return Un pointeur vers la structure `RendererManager` initialisée, ou NULL en cas d'échec.
 */
RendererManager* RendererManager_Init(SDL_Renderer* sdl_renderer, int max_renderers);

/**
 * @brief Initialise un objet `Renderer` avec une fonction de rendu, un objet à rendre et un index Z.
 * 
 * @param renderFunction Fonction de rendu pour l'objet.
 * @param object Pointeur vers l'objet affichable.
 * @param z_index Index Z pour déterminer l'ordre de rendu. Plus la valeur est grande et plus elle sera proche de la caméra.
 * @return Un pointeur vers la structure `Renderer` initialisée.
 */
Renderer* Renderer_Init(void* renderFunction, void* object, int z_index);

/**
 * @brief Aplatit les objets de rendu dans le `RendererManager`.
 * 
 * @param manager Pointeur vers la structure `RendererManager` à aplatir.
 */
void RendererManager_Flatten(RendererManager* manager);

/**
 * @brief Ajoute plusieurs objets de rendu au `RendererManager`.
 * 
 * @param manager Pointeur vers la structure `RendererManager` dans laquelle ajouter les objets.
 * @param num_renderers Nombre d'objets de rendu à ajouter.
 * @param ... Liste des objets de rendu à ajouter, suivis de leurs paramètres respectifs.
 */
void RendererManager_Add(RendererManager* manager, ...);

/**
 * @brief Trie les objets de rendu dans le `RendererManager` par index Z.
 * 
 * @param manager Pointeur vers la structure `RendererManager` à trier.
 */
void RendererManager_Sort(RendererManager* manager);

/**
 * @brief Rend tous les objets dans le `RendererManager`.
 * 
 * @param manager Pointeur vers la structure `RendererManager` contenant les objets à rendre.
 */
void RendererManager_Render(RendererManager* manager);

/**
 * @brief Met à jour les animations dynamiques d'un objet `Renderer`.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à mettre à jour.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Update_DynamicAnimation(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Met à jour les animations statiques d'un objet `Renderer`.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à mettre à jour.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Update_StaticAnimation(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Met à jour les sprites d'un objet `Renderer`.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à mettre à jour.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Update_Sprite(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Met à jour les labels d'un objet `Renderer`.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à mettre à jour.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Update_Label(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Met à jour la fenêtre d'un objet `Renderer`.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à mettre à jour.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Update_Window(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Affiche les animations dynamiques d'un objet `Renderer`.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Show_DynamicAnimation(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Affiche les animations statiques d'un objet `Renderer`.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Show_StaticAnimation(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Affiche les sprites d'un objet `Renderer`.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Show_Sprite(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Affiche les labels d'un objet `Renderer`.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Show_Label(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Affiche la fenêtre d'un objet `Renderer`.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Show_Window(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Fonction de rendu pour le `StaticAnimationManager`.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Renderer2_StaticAnimationManager(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Fonction de rendu pour les animations dynamiques.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Renderer_DynamicAnimation(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Fonction de rendu pour les animations statiques.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Renderer_StaticAnimation(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Fonction de rendu pour les sprites.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Renderer_Sprite(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Fonction de rendu pour les widget.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Renderer_Widget(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Fonction de rendu pour les panels.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Renderer_Panel(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Fonction de rendu pour les labels.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Renderer_Label(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Fonction de rendu pour les boutons.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Renderer_Button(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Rend un champ de saisie (InputField) à l'écran.
 *
 * @param renderer Le renderer contenant l'objet InputField.
 * @param sdl_renderer Le renderer SDL utilisé pour dessiner l'InputField.
 */
void Renderer_InputField(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Fonction de rendu pour la tooltip.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Renderer_Tooltip(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Fonction de rendu pour la fenêtre.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Renderer_Window(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Fonction de rendu pour le `DynamicAnimationManager`.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Renderer_DynamicAnimationManager(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Fonction de rendu pour le `StaticAnimationManager`.
 * 
 * @param renderer Pointeur vers la structure `Renderer` à afficher.
 * @param sdl_renderer Pointeur vers le renderer SDL utilisé pour le rendu.
 */
void Renderer_StaticAnimationManager(Renderer* renderer, SDL_Renderer* sdl_renderer);

/**
 * @brief Trie récursivement un tableau de renderers en utilisant l'algorithme de tri fusion.
 * 
 * @param renderers Un tableau de pointeurs vers des structures Renderer à trier.
 * @param l L'indice gauche du sous-tableau à trier.
 * @param r L'indice droit du sous-tableau à trier.
 */
void Renderer_Sort_MergeRecursive(Renderer** renderers, int l, int r);

/**
 * @brief Fusionne deux sous-tableaux d'un tableau de renderers.
 * 
 * Les sous-tableaux sont renderers[l..m] et renderers[m+1..r].
 * 
 * @param renderers Un tableau de pointeurs vers des structures Renderer à trier.
 * @param l L'indice gauche du premier sous-tableau.
 * @param m L'indice milieu, séparant les deux sous-tableaux.
 * @param r L'indice droit du second sous-tableau.
 */
void Renderer_Sort_Merge(Renderer** renderers, int l, int m, int r);

#endif // RENDERER_H
