#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "game_system.h"
#include "../../Entities/include/entity.h"
#include "../../Globals/include/constants.h"

typedef struct EventType {
    char name[MAX_EVENT_NAME_LENGTH];
    int index;
} EventType;

// Structure de l'événement
typedef struct Event {
    EventType type; 
    char name[MAX_EVENT_TYPE_NAME_LENGTH];       // Nom de l'événement (nouvel attribut ajouté)
    void* data;          // Pointeur générique pour les données associées à l'événement
} Event;


// Pointeur de fonction pour les écouteurs d'événements
typedef void (*EventListener)(Event event);

// Structure pour gérer les écouteurs d'événements
typedef struct EventListeners {
    EventType type;
    EventListener listeners[MAX_LISTENERS];
    int listenerCount;
} EventListeners;

// Structure pour stocker les bindings d'événements
typedef struct EventBinding {
    SDL_Keycode key;
    EventType eventType;
    void* eventData;
} EventBinding;

// Fonctions pour gérer les événements
void initializeEventTypes();
void addEventListener(EventType type, EventListener listener);
void removeAllEvents(Entity entity);
void removeEventListener(EventType type, EventListener listener);
void emitEvent(Event event);
void bindEvent(Entity entity, SDL_Keycode key, EventType eventType, void* eventData);

void processEvents();
void updateEvent();  // Pour gérer les événements SDL et les convertir en événements internes

// Fonction pour ajouter un type d'événement dynamique
int addEventType(const char* eventName);

// Fonction pour récupérer l'index d'un événement dynamique par son nom
EventType getEventType(const char* eventName);
int getEventTypeIndex(const char* eventName);

// Fonction qui vérifie si le nom d'un événement correspond à une chaîne donnée
bool isEventName(Event event, const char* name);

#endif // EVENT_SYSTEM_H