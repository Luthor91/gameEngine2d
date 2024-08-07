#include "../Core/Utilities/include/core.h"

/**
 * @brief Exemple de programme pour afficher une fenêtre, un panneau, et d'autres composants avec SDL.
 * 
 * Ce programme démontre comment initialiser et gérer une application SDL en configurant et rendant divers éléments graphiques. 
 * Il se compose des étapes suivantes :
 * 
 * 1. **Initialisation des composants** :
 *    - Configure les éléments de base comme la fenêtre et le panneau.
 *    - Crée et initialise divers composants graphiques comme les sprites, les labels, les champs de saisie, les boutons, etc.
 * 
 * 2. **Configuration des paramètres** :
 *    - Définie les propriétés des composants graphiques (position, taille, couleur, etc.) en utilisant des chaînes de paramètres.
 * 
 * 3. **Gestion des événements** :
 *    - Associe des actions spécifiques (comme le clic sur un bouton) à des gestionnaires d'événements.
 * 
 * 4. **Initialisation des gestionnaires de rendu et d'événements** :
 *    - Prépare les gestionnaires pour le rendu des composants et la gestion des événements.
 * 
 * 5. **Boucle principale** :
 *    - Traite les événements.
 *    - Rend les composants à l'écran à chaque frame.
 *    - Contrôle le taux de rafraîchissement de l'écran.
 * 
 * 6. **Nettoyage** :
 *    - Libère toutes les ressources avant de fermer l'application.
 * 
 * Chaque ajout ou configuration de composant suit cette méthodologie :
 *  - **Initialisation de l'élément** : Crée et configure le composant.
 *  - **Initialisation de son renderer** : Configure le renderer pour le composant.
 *  - **Ajout du renderer dans le gestionnaire de rendu** : Ajoute le renderer au gestionnaire pour le rendu à l'écran.
 */

void Event_Space_Pressed(void* object, SDL_Event* event, void* value) {
    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_SPACE) {
        Force* new_force = Force_Init(5.0, DIRECTION_SOUTH);
        ForceManager* manager = (ForceManager*)value;
        if (new_force != NULL) {
            ForceManager_AddForce(manager, new_force);
        }
    }
}

int main(int argc, char* argv[]) {
    // Initialisation des composants du programme.
    if (Init_All() != 0) return 1;

    // Création et initialisation des composants graphiques.
    Window* window = Window_Init(NULL, NULL, NULL);
    Sprite* sprite_1 = Sprite_Init(NULL, NULL);
    Sprite* sprite_2 = Sprite_Init(NULL, NULL);
    Sprite_Set(sprite_1, "position:5%,5%;");
    Sprite_Set(sprite_2, "position:left,bottom;");

    RigidBody* r_body1 = RigidBody_Init(sprite_1->transform, NULL);
    RigidBody* r_body2 = RigidBody_Init(sprite_2->transform, NULL);
    ForceManager_AddForce(r_body1->physics->forces, &(Force){9.81f, DIRECTION_SOUTH});

    // Initialisation des gestionnaires de rendu et d'événements.
    RendererManager* r_manager = RendererManager_Init(NULL, DEFAULT_MAX_RENDERER);
    RigidBodyManager* rb_manager = RigidBodyManager_Init(DEFAULT_MAX_BODIES);
    PhysicsBodies* p_bodies = PhysicBodies_Init(NULL, rb_manager, NULL);
    EventManager* evt_manager = EventManager_Init(DEFAULT_MAX_EVENT);

    // Création et initialisation des renderers pour chaque composant.
    Renderer* renderer_window = Renderer_Init(Renderer_Window, window, 0);
    Renderer* renderer_sprite_1 = Renderer_Init(Renderer_Sprite, sprite_1, 2);
    Renderer* renderer_sprite_2 = Renderer_Init(Renderer_Sprite, sprite_2, 2);

    Event* evt_space = Event_Init(NULL, Event_Space_Pressed, r_body1->physics->forces);
    
    // Ajout des renderers et des événements aux gestionnaires respectifs.
    RendererManager_Add(r_manager, renderer_window, renderer_sprite_1, renderer_sprite_2, NULL);
    RigidBodyManager_Add(rb_manager, r_body1, r_body2, NULL);
    EventManager_Add(evt_manager, evt_space, NULL);

    // Tri des renderers dans le gestionnaire de rendu.
    RendererManager_Sort(r_manager);

    // Boucle principale du programme.
    while (!sdl_quit_flag) {
        // Gestion des événements.
        EventManager_HandleEvents(evt_manager, &sdl_quit_flag);
        PhysicBodies_Update(p_bodies, Time_GetDelta());
        // Ici, vous pouvez ajouter des fonctionnalités supplémentaires si nécessaire.
        printf("rbody: pos(x,y):(%d,%d) ; vel(%lf,%lf) ; accel(%lf,%lf)\n", 
            r_body1->transform->position->x, r_body1->transform->position->y, 
            r_body1->physics->velocity->x, r_body1->physics->velocity->y,
            r_body1->physics->acceleration->x, r_body1->physics->acceleration->x);
        // Rendu des composants à l'écran.
        RendererManager_Render(r_manager);

        // Limite le nombre de frames par seconde (FPS).
        Time_SetFPSLimit(DEFAULT_FPS_AVERAGE);
    }

    // Nettoyage et fermeture de tous les composants.
    Exit_All(window);

    return 0;
}
