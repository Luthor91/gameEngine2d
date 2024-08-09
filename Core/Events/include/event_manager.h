#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../Events/include/event.h"

#define DEFAULT_EVENT EventManager_Init(DEFAULT_MAX_EVENT)
#define DEFAULT_MAX_EVENT 4096

// Structure représentant un événement
typedef struct Event {
    void* object;           ///< Pointeur vers l'objet associé à l'événement
    void* callback;         ///< Pointeur vers la fonction de rappel (utilisé comme void*)
    void* transfered_value;
    void* returned_value;
} Event;

// Structure représentant le gestionnaire d'événements
typedef struct EventManager {
    Event* events;  ///< Tableau dynamique d'événements
    int current_index; ///< Index actuel dans le tableau
    int max_index;     ///< Index maximum dans le tableau
} EventManager;

extern EventManager* EVENT_MANAGER;
extern int sdl_quit_flag;

/**
 * @brief Initialise le gestionnaire d'événements
 * 
 * @param initial_size Taille initiale du tableau d'événements
 * @return Pointeur vers le gestionnaire d'événements initialisé
 */
EventManager* EventManager_Init(int initial_size);

/**
 * @brief Initialise un événement
 * 
 * @param object Pointeur vers l'objet associé à l'événement
 * @param callback Fonction de rappel pour traiter l'événement
 * @return Pointeur vers l'événement initialisé
 */
Event* Event_Init(void* object, void* callback, void* transfered_value, void* returned_value);

/**
 * @brief Ajoute des événements au gestionnaire d'événements
 * 
 * @param manager Pointeur vers le gestionnaire d'événements
 * @param num_events Nombre d'événements à ajouter
 * @param ... Liste variadique des événements à ajouter
 * @return 0 en cas de succès, -1 en cas d'échec
 */
int EventManager_Add(EventManager* manager, ...);

/**
 * @brief Gère tous les événements en attente
 * 
 * @param manager Pointeur vers le gestionnaire d'événements
 */
void EventManager_HandleEvents(EventManager* manager);

/**
 * @brief Libère les ressources allouées pour le gestionnaire d'événements
 * 
 * @param manager Pointeur vers le gestionnaire d'événements à libérer
 */
void EventManager_Destroy(EventManager* manager);

#endif // EVENT_MANAGER_H
