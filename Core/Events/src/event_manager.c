#include "../include/event_manager.h"

/**
 * @brief Initialise le gestionnaire d'événements
 * 
 * @param initial_size Taille initiale du tableau d'événements
 * @return Pointeur vers le gestionnaire d'événements initialisé
 */
EventManager* EventManager_Init(int initial_size) {
    EventManager* manager = (EventManager*)malloc(sizeof(EventManager));
    if (!manager) {
        printf("EventManager_Init: Échec de l'allocation de mémoire pour le gestionnaire d'événements.\n");
        return NULL;
    }

    manager->events = (Event*)malloc(initial_size * sizeof(Event));
    if (!manager->events) {
        printf("EventManager_Init: Échec de l'allocation de mémoire pour le tableau d'événements.\n");
        free(manager);
        return NULL;
    }

    manager->current_index = 0;
    manager->max_index = initial_size;

    return manager;
}

/**
 * @brief Initialise un événement
 * 
 * @param object Pointeur vers l'objet associé à l'événement
 * @param callback Fonction de rappel pour traiter l'événement
 * @return Pointeur vers l'événement initialisé
 */
Event* Event_Init(void* object, void* callback, void* transfered_value, void* returned_value) {
    Event* event = (Event*)malloc(sizeof(Event));
    if (!event) {
        printf("Event_Init: Échec de l'allocation de mémoire pour l'événement.\n");
        return NULL;
    }
    event->object = object;
    event->callback = callback;
    event->transfered_value = transfered_value;
    event->returned_value = returned_value;
    return event;
}

/**
 * @brief Ajoute des événements au gestionnaire d'événements
 * 
 * @param manager Pointeur vers le gestionnaire d'événements
 * @param num_events Nombre d'événements à ajouter
 * @param ... Liste variadique des événements à ajouter
 * @return 0 en cas de succès, -1 en cas d'échec
 */
int EventManager_Add(EventManager* manager, ...) {
    va_list args;
    va_start(args, manager);

    int num_events = 0;
    Event* event;

    // Compter les arguments variadiques jusqu'à rencontrer NULL
    while ((event = va_arg(args, Event*)) != NULL) {
        num_events++;
    }
    va_end(args);
    
    va_start(args, manager); // Réinitialiser va_list pour réutilisation

    // Itérer et ajouter les événements
    for (int i = 0; i < num_events; i++) {
        event = va_arg(args, Event*);

        if (!event) {
            fprintf(stderr, "EventManager_Add: Événement à l'index %d est NULL\n", i);
            va_end(args);
            return -1;
        }

        if (manager->current_index >= manager->max_index) {
            int new_size = manager->max_index * 2;
            Event* new_events = (Event*)realloc(manager->events, new_size * sizeof(Event));
            if (!new_events) {
                printf("EventManager_Add: Échec de la réallocation de mémoire pour le tableau d'événements.\n");
                va_end(args);
                return -1;
            }
            manager->events = new_events;
            manager->max_index = new_size;
        }

        manager->events[manager->current_index].object = event->object;
        manager->events[manager->current_index].callback = event->callback;
        manager->events[manager->current_index].transfered_value = event->transfered_value;
        manager->events[manager->current_index].returned_value = event->returned_value;
        manager->current_index++;
    }

    va_end(args);
    return 0;
}

/**
 * @brief Gère tous les événements en attente
 * 
 * @param manager Pointeur vers le gestionnaire d'événements
 */
void EventManager_HandleEvents(EventManager* manager, int* sdl_quit_flag) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *sdl_quit_flag = 1;
            return;
        }

        for (int i = 0; i < manager->current_index; i++) {
            void (*callback)(void*, SDL_Event*) = (void (*)(void*, SDL_Event*))manager->events[i].callback;
            callback(manager->events[i].object, &event);
        }
    }
}

/**
 * @brief Libère les ressources allouées pour le gestionnaire d'événements
 * 
 * @param manager Pointeur vers le gestionnaire d'événements à libérer
 */
void EventManager_Destroy(EventManager* manager) {
    if (manager) {
        free(manager->events);
        free(manager);
    }
}
