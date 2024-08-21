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
#define MAX_KEYS 512
#define MAX_BINDINGS 256
#define MAX_EVENTS 256                // Nombre maximum d'événements dans la file d'attente
#define MAX_LISTENERS 64              // Nombre maximum de types d'écouteurs d'événements

#define MAX_EVENT_QUEUE_SIZE MAX_EVENTS       // Taille maximale de la file d'attente d'événements (identique à MAX_EVENTS)
#define MAX_EVENT_TYPE_COUNT MAX_LISTENERS    // Nombre maximum de types d'événements (identique à MAX_LISTENERS)
#define MAX_LISTENER_COUNT MAX_LISTENERS      // Nombre maximum de types d'écouteurs d'événements (identique à MAX_LISTENERS)
#define MAX_LISTENERS_PER_EVENT 16            // Nombre maximum d'écouteurs pour un type d'événement donné

// Types d'événements
typedef enum EventType {
    EVENT_TYPE_MOVE,
    EVENT_TYPE_JUMP,
    EVENT_TYPE_SHOOT,
    EVENT_TYPE_DASH,
    EVENT_TYPE_DEATH,
    EVENT_TYPE_LEVEL_UP,
    EVENT_TYPE_COLLIDE,
    EVENT_TYPE_INFO,
    EVENT_TYPE_QUIT,
    EVENT_TYPE_KEYDOWN,
    EVENT_TYPE_KEYUP,
    EVENT_TYPE_MIDDLE_MOUSECLICK,
    EVENT_TYPE_RIGHT_MOUSECLICK,
    EVENT_TYPE_LEFT_MOUSECLICK,
    EVENT_TYPE_MIDDLE_MOUSEHELD,
    EVENT_TYPE_RIGHT_MOUSEHELD,
    EVENT_TYPE_LEFT_MOUSEHELD,
    EVENT_TYPE_TIMER_EXPIRED,
    EVENT_TYPE_GENERIC,
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

// Fonctions pour gérer les événements
void addEventListener(EventType type, EventListener listener);
void removeEventListener(EventType type, EventListener listener);
void emitEvent(Event event);
void bindEvent(Entity entity, SDL_Keycode key, EventType eventType, void* eventData);

void processEvents();
void updateEvent();  // Pour gérer les événements SDL et les convertir en événements internes

#endif // EVENT_SYSTEM_H