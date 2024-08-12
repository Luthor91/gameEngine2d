#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTS 256
#define MAX_LISTENERS 64

typedef enum EventType {
    EVENT_TYPE_MOVE,
    EVENT_TYPE_JUMP,
    EVENT_TYPE_SHOOT,
    EVENT_TYPE_QUIT, // Ajoutez les autres types d'événements nécessaires
} EventType;

typedef struct Event {
    EventType type;
    void* data; // Pointeur générique pour les données associées à l'événement
} Event;

typedef void (*EventListener)(Event event);

typedef struct EventListeners {
    EventType type;
    EventListener listeners[MAX_LISTENERS];
    int listenerCount;
} EventListeners;

void addEventListener(EventType type, EventListener listener);
void removeEventListener(EventType type, EventListener listener);
void emitEvent(Event event);
void processEvents();

#endif // EVENT_SYSTEM_H
