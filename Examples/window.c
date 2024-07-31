#include "../Core/Utilities/include/core.h"

/**
 * Programme d'exemple pour afficher une fenêtre vide avec les assets de base.
 * 
 * Ce programme initialise tous les composants nécessaires pour créer une fenêtre SDL,
 * configure un gestionnaire de rendu pour afficher le contenu, et entre dans une boucle
 * principale où il rend le contenu à chaque frame tout en vérifiant les événements.
 * La boucle principale continue jusqu'à ce que l'utilisateur déclenche une action de sortie.
 * 
 * Chaque ajout de composant affichable dans le code se fait de la manière suivant :
 *  - Initialisation de l'élement
 *  - Initialisation de son renderer
 *  - Ajout du renderer dans le gestionnaire de rendu
 * 
 */
int main(int argc, char* argv[]) {

    // Initialisation de tous les composants nécessaires pour le programme.
    if (Init_All() != 0) return 1;
    
    // Initialisation d'une fenêtre avec les paramètres par défaut.
    Window* window = Window_Init(NULL, NULL, NULL);

    // Initialisation du gestionnaire de rendu avec la taille maximale des objets à rendre.
    RendererManager* manager = RendererManager_Init(window->renderer, DEFAULT_MAX_RENDERER);

    // Création et initialisation d'un renderer pour afficher la fenêtre.
    Renderer* renderer = Renderer_Init(Renderer_Window, window, 0);

    // Ajout du renderer au gestionnaire de rendu.
    RendererManager_Add(manager, 1, renderer); 
    
    int quit = 0; // Variable pour contrôler la boucle principale du programme.

    // Boucle principale du programme.
    while (!quit) {
        
        Event_Exit(&quit); // Vérifie l'event de sortie du programme

        /**
         *  Si vous voulez ajouter des fonctionnalités
         *  Idéalement le code devrait se situer à la place de ce commentaire
         */

        RendererManager_Render(manager); // Rend le contenu à afficher en utilisant le gestionnaire de rendu.

        Time_SetFPSLimit(60); // Définit la limite de frames par seconde (FPS) pour contrôler la vitesse de rafraîchissement.
    }

    Exit_All(window); // Nettoie et ferme tous les composants

    return 0;
}
