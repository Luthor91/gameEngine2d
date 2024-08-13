#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "game_system.h"
#include "../../Entities/include/entity.h"


// Définitions des constantes
#define MAX_EVENTS 256
#define MAX_LISTENERS 64

#define MAX_KEYS 512
#define MAX_BINDINGS 256

// Types d'événements
typedef enum EventType {
    EVENT_TYPE_MOVE,
    EVENT_TYPE_JUMP,
    EVENT_TYPE_SHOOT,
    EVENT_TYPE_DASH,
    EVENT_TYPE_QUIT,
    EVENT_TYPE_KEYDOWN,
    EVENT_TYPE_KEYUP,
    // Ajoutez ici d'autres types d'événements nécessaires
} EventType;

// Structure de l'événement
typedef struct Event {
    EventType type;
    void* data; // Pointeur générique pour les données associées à l'événement
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

// Variables globales pour gérer les événements
static EventBinding entityBindings[MAX_ENTITIES][MAX_BINDINGS] = {0};
static EventListeners eventListeners[MAX_EVENTS];
static Event eventQueue[MAX_EVENTS];
static int eventQueueCount = 0;
static int listenerCount = 0;

// Fonctions pour gérer les événements
void addEventListener(EventType type, EventListener listener);
void removeEventListener(EventType type, EventListener listener);
void emitEvent(Event event);
void bindEvent(Entity entity, SDL_Keycode key, EventType eventType, void* eventData);

void processEvents();
void updateEvent();  // Pour gérer les événements SDL et les convertir en événements internes

#endif // EVENT_SYSTEM_H
