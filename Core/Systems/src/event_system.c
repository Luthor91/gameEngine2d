#include "../include/event_system.h"

static EventListeners eventListeners[MAX_EVENTS];
static Event eventQueue[MAX_EVENTS];
static int eventQueueCount = 0;

void addEventListener(EventType type, EventListener listener) {
    for (int i = 0; i < MAX_EVENTS; ++i) {
        if (eventListeners[i].type == type) {
            if (eventListeners[i].listenerCount < MAX_LISTENERS) {
                eventListeners[i].listeners[eventListeners[i].listenerCount++] = listener;
            } else {
                printf("Max listeners reached for event type %d\n", type);
            }
            return;
        } else if (eventListeners[i].listenerCount == 0) {
            eventListeners[i].type = type;
            eventListeners[i].listeners[0] = listener;
            eventListeners[i].listenerCount = 1;
            return;
        }
    }
}

void removeEventListener(EventType type, EventListener listener) {
    for (int i = 0; i < MAX_EVENTS; ++i) {
        if (eventListeners[i].type == type) {
            for (int j = 0; j < eventListeners[i].listenerCount; ++j) {
                if (eventListeners[i].listeners[j] == listener) {
                    memmove(&eventListeners[i].listeners[j], &eventListeners[i].listeners[j + 1],
                            sizeof(EventListener) * (eventListeners[i].listenerCount - j - 1));
                    eventListeners[i].listenerCount--;
                    return;
                }
            }
        }
    }
}

void emitEvent(Event event) {
    if (eventQueueCount < MAX_EVENTS) {
        eventQueue[eventQueueCount++] = event;
    } else {
        printf("Event queue overflow\n");
    }
}

void processEvents() {
    for (int i = 0; i < eventQueueCount; ++i) {
        Event event = eventQueue[i];
        for (int j = 0; j < MAX_EVENTS; ++j) {
            if (eventListeners[j].type == event.type) {
                for (int k = 0; k < eventListeners[j].listenerCount; ++k) {
                    eventListeners[j].listeners[k](event);
                }
            }
        }
    }
    eventQueueCount = 0; // Réinitialise la queue après le traitement
}
