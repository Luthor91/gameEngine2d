#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../Entities/include/entity.h"
#include "../../Components/include/input_component.h"
#include "../../Components/include/velocity_component.h"
#include "../../Components/include/transform_component.h"

// Déclaration des types d'événements
#define EVENT_TYPE_MOVE 1
#define EVENT_TYPE_JUMP 2
#define EVENT_TYPE_QUIT 3
#define EVENT_TYPE_KEYDOWN 4
#define EVENT_TYPE_KEYUP 5

typedef struct Event {
    int type;
    void* data;
} Event;

#define MAX_EVENT_LISTENERS 10

typedef struct {
    int eventType;
    void (*callback)(Event event);
} EventListener;

static EventListener eventListeners[MAX_EVENT_LISTENERS];
static int listenerCount = 0;
static Event eventQueue[MAX_EVENT_LISTENERS];
static int eventQueueSize = 0;

void addEventListener(int eventType, void (*callback)(Event event));
void emitEvent(Event event);
void processEvents();
void updateInput();

#endif // EVENT_MANAGER_H
