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

#define MAX_KEYS 512
#define MAX_BINDINGS 4096
#define MAX_EVENTS 16384                // Nombre maximum d'événements dans la file d'attente
#define MAX_LISTENERS 8192              // Nombre maximum de types d'écouteurs d'événements

#define MAX_EVENT_TYPE_NAME_LENGTH 32
#define MAX_EVENT_NAME_LENGTH 32

#define MAX_EVENT_QUEUE_SIZE MAX_EVENTS       // Taille maximale de la file d'attente d'événements (identique à MAX_EVENTS)
#define MAX_EVENT_COUNT MAX_LISTENERS    // Nombre maximum de types d'événements (identique à MAX_LISTENERS)
#define MAX_LISTENER_COUNT MAX_LISTENERS      // Nombre maximum de types d'écouteurs d'événements (identique à MAX_LISTENERS)
#define MAX_LISTENERS_PER_EVENT 4096            // Nombre maximum d'écouteurs pour un type d'événement donné
#define MAX_EVENT_TYPES 4096 // Nombre total maximal de types d'événements

// Valeur spéciale pour indiquer un échec
#define EVENT_NOT_FOUND_INDEX -1
#define EVENT_NOT_FOUND (EventType){"UNKNOWN_EVENT_TYPE\0", EVENT_NOT_FOUND_INDEX}

// Liste des types d'événements prédéfinis
#define EVENT_LIST \
    X(EVENT_MOVE) \
    X(EVENT_JUMP) \
    X(EVENT_SHOOT) \
    X(EVENT_DASH) \
    X(EVENT_DEATH) \
    X(EVENT_LEVEL_UP) \
    X(EVENT_COLLIDE) \
    X(EVENT_INFO) \
    X(EVENT_QUIT) \
    X(EVENT_KEYDOWN) \
    X(EVENT_KEYUP) \
    X(EVENT_MIDDLE_MOUSECLICK) \
    X(EVENT_RIGHT_MOUSECLICK) \
    X(EVENT_LEFT_MOUSECLICK) \
    X(EVENT_MIDDLE_MOUSEHELD) \
    X(EVENT_RIGHT_MOUSEHELD) \
    X(EVENT_LEFT_MOUSEHELD) \
    X(EVENT_TIMER_EXPIRED) \
    X(EVENT_GENERIC) \
    /* Ajoutez ici d'autres types d'événements nécessaires */
    
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