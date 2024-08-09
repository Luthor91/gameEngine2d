#include "../Core/Utilities/include/core.h"

void Event_Space_Pressed(void* object, SDL_Event* event, void* entry, void* returned) {
    if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_SPACE) {
        Signal_Emit(object, NULL);
    }
}

// Fonction de gestion pour les signaux
void Signal_Space_Pressed(void* data) {
    if (data == NULL) { return; }
    int* count = (int*)data;
    (*count)++;
    printf("Signal_Space_Pressed: pressed Count: %d\n", *count);
}

int main(int argc, char* argv[]) {
    // Initialisation des composants du programme.
    if (Init_All() == 0) return 1;

    int data = 42;  

    // Création et initialisation des renderers pour chaque composant.
    Renderer* r_window = Renderer_Init(Renderer_Window, CURRENT_WINDOW, 0);
    Signal* signal = Signal_Init(Signal_Space_Pressed, &data);
    Event* evt_space1 = Event_Init(signal, Event_Space_Pressed, NULL, NULL);
    // Ajout des renderers et des événements aux gestionnaires respectifs.
    RendererManager_Add(RENDERER_MANAGER, r_window, NULL);
    EventManager_Add(EVENT_MANAGER, evt_space1, NULL);

    // Tri des renderers dans le gestionnaire de rendu.
    RendererManager_Sort(RENDERER_MANAGER);

    // Boucle principale du programme.
    while (!sdl_quit_flag) {
        // Gestion des événements.
        EventManager_HandleEvents(EVENT_MANAGER);
        Collision_HandleAll(PHYSICSBODIES_MANAGER);
        PhysicBodies_Update(PHYSICSBODIES_MANAGER, TIME_DELTA);
        TimerManager_Update(TIMER_MANAGER);

        // Ici, vous pouvez ajouter des fonctionnalités supplémentaires si nécessaire.

        RendererManager_Render(RENDERER_MANAGER);
        Time_SetFPSLimit(DEFAULT_FPS_AVERAGE);
    }

    // Nettoyage et fermeture de tous les composants.
    Exit_All(CURRENT_WINDOW);

    return 0;
}
