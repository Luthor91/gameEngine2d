#include "../Core/Utilities/include/core.h"

/**
 * @brief Programme d'exemple pour afficher une fenêtre et un panel avec les assets de base.
 * 
 * Ce programme initialise tous les composants nécessaires pour créer une fenêtre SDL,
 * configure un gestionnaire de rendu pour afficher le contenu, et entre dans une boucle
 * principale où il rend le contenu à chaque frame tout en vérifiant les événements.
 * La boucle principale continue jusqu'à ce que l'utilisateur déclenche une action de sortie.
 * 
 * Chaque ajout de composant affichable dans le code se fait de la manière suivante :
 *  - Initialisation de l'élément
 *  - Initialisation de son renderer
 *  - Ajout du renderer dans le gestionnaire de rendu
 * 
 */

int main(int argc, char* argv[]) {
    // Initialisation de tous les composants nécessaires pour le programme.
    if (Init_All() != 0) return 1;

    // Initialisation des composants graphiques
    Window* window = Window_Init(NULL, NULL, NULL);
    
    // Initialisation du gestionnaire de rendu avec la taille maximale des objets à rendre.
    RendererManager* manager = RendererManager_Init(NULL, DEFAULT_MAX_RENDERER);
    EventManager* event_manager = EventManager_Init(DEFAULT_MAX_EVENT);

    // Création et initialisation des renderers
    Renderer* renderer_window = Renderer_Init(Renderer_Window, window, 0);

    // Ajout des renderers au gestionnaire de rendu.
    RendererManager_Add(manager, renderer_window, NULL);

    RendererManager_Sort(manager);

    // Boucle principale du programme.
    while (!sdl_quit_flag) {
        EventManager_HandleEvents(event_manager, &sdl_quit_flag);

        /**
         *  Si vous voulez ajouter des fonctionnalités
         *  Idéalement le code devrait se situer à la place de ce commentaire
         */

        RendererManager_Render(manager); // Rend le contenu à afficher en utilisant le gestionnaire de rendu.

        Time_SetFPSLimit(DEFAULT_FPS_AVERAGE); // Définit la limite de frames par seconde (FPS) pour contrôler la vitesse de rafraîchissement.
    }

    Exit_All(window); // Nettoie et ferme tous les composants

    return 0;
}
