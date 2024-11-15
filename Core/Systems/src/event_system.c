#include "../include/event_system.h"

// Variables globales pour gérer les événements
static EventBinding entityBindings[MAX_ENTITIES][MAX_BINDINGS] = {0};
static EventListeners eventListeners[MAX_EVENTS] = {0};
static Event eventQueue[MAX_EVENTS] = {0};
static int eventQueueCount = 0;
static int listenerCount = 0;

static EventType eventTypes[MAX_EVENT_TYPES] = {0};
static int eventTypeCount = 0;

int Init_event_types() {
    const char* predefinedEventNames[] = {
        "EVENT_MOVE",
        "EVENT_JUMP",
        "EVENT_SHOOT",
        "EVENT_DASH",
        "EVENT_DEATH",
        "EVENT_LEVEL_UP",
        "EVENT_COLLIDE",
        "EVENT_INFO",
        "EVENT_QUIT",
        "EVENT_KEYDOWN",
        "EVENT_KEYUP",
        "EVENT_MIDDLE_MOUSECLICK",
        "EVENT_RIGHT_MOUSECLICK",
        "EVENT_LEFT_MOUSECLICK",
        "EVENT_MIDDLE_MOUSEHELD",
        "EVENT_RIGHT_MOUSEHELD",
        "EVENT_LEFT_MOUSEHELD",
        "EVENT_TIMER_EXPIRED",
        "EVENT_GENERIC"
    };

    int predefinedEventCount = sizeof(predefinedEventNames) / sizeof(predefinedEventNames[0]);

    for (int i = 0; i < predefinedEventCount; ++i) {
        if (eventTypeCount < MAX_EVENT_TYPES) {
            strncpy(eventTypes[eventTypeCount].name, predefinedEventNames[i], MAX_EVENT_NAME_LENGTH - 1);
            eventTypes[eventTypeCount].name[MAX_EVENT_NAME_LENGTH - 1] = '\0';
            eventTypes[eventTypeCount].index = eventTypeCount;
            eventTypeCount++;
        } else {
            fprintf(stderr, "Error: Maximum event types reached. Cannot add more events.\n");
            return 0;
        }
    }

    return 1;
}

// Fonction pour créer un Event avec un type et un nom, et avec data initialisé à NULL
Event Event_Create(EventType type, const char* name) {
    Event event;
    event.type = type;
    event.data = NULL;  // Initialise le pointeur data à NULL
    strncpy(event.name, name, sizeof(event.name) - 1);
    event.name[sizeof(event.name) - 1] = '\0'; // Ajoute un terminateur de chaîne

    return event;
}

// Ajout d'un écouteur d'événements
void addEventListener(EventType type, EventListener listener) {
    for (int i = 0; i < MAX_EVENTS; ++i) {
        if (eventListeners[i].type.index == type.index) {
            if (eventListeners[i].listenerCount < MAX_LISTENERS) {
                eventListeners[i].listeners[eventListeners[i].listenerCount++] = listener;
            } else {
                printf("Max listeners reached for event type %d\n", type.index);
            }
            return;
        } else if (eventListeners[i].listenerCount == 0) {
            eventListeners[i].type = type;
            eventListeners[i].listeners[0] = listener;
            eventListeners[i].listenerCount = 1;
            listenerCount++;
            return;
        }
    }
}

// Fonction pour supprimer tous les événements associés à une entité
void removeAllEvents(Entity entity) {
    if (entity >= MAX_ENTITIES) {
        return;
    }

    for (int i = 0; i < MAX_BINDINGS; ++i) {
        if (entityBindings[entity][i].key != 0) {
            entityBindings[entity][i].key = 0; 
            entityBindings[entity][i].event.type = (EventType){0};

            // Libérer la mémoire associée à eventData si elle est allouée dynamiquement
            if (entityBindings[entity][i].event.data != NULL) {
                free(entityBindings[entity][i].event.data);
                entityBindings[entity][i].event.data = NULL;
            }
        }
    }
}

// Retrait d'un écouteur d'événements
void removeEventListener(EventType type, EventListener listener) {
    for (int i = 0; i < MAX_EVENTS; ++i) {
        if (eventListeners[i].type.index == type.index) {
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

// Émettre un événement
void emitEvent(Event event) {
    if (eventQueueCount < MAX_EVENTS) {
        eventQueue[eventQueueCount++] = event;
    } else {
        printf("Event queue is full, cannot emit event of type %d\n", event.type.index);
    }
}

void bindEvent(Entity entity, SDL_Keycode key, Event event) {
    for (int i = 0; i < MAX_BINDINGS; ++i) {
        if (entityBindings[entity][i].key == key || entityBindings[entity][i].key == 0) {
            entityBindings[entity][i].key = key;
            entityBindings[entity][i].event = event;
            return;
        }
    }
    printf("Warning: Max bindings reached for entity %ld\n", entity);
}

void processEvents() {
    if (eventQueueCount == 0) {
        return;
    }

    for (int i = 0; i < eventQueueCount; ++i) {
        if (i < 0 || i >= MAX_EVENT_QUEUE_SIZE) {
            printf("Error: Invalid event index %d\n", i);
            continue;
        }
        
        Event event = eventQueue[i];

        if (event.type.index < 0 || event.type.index >= MAX_EVENT_COUNT) {
            printf("Error: Invalid event type %d\n", event.type.index);
            continue;
        }

        for (int j = 0; j < listenerCount; ++j) {
            if (j < 0 || j >= MAX_LISTENER_COUNT) {
                printf("Error: Invalid listener index %d\n", j);
                continue;
            }

            if (eventListeners[j].type.index == event.type.index) {
                for (int k = 0; k < eventListeners[j].listenerCount; ++k) {
                    if (k < 0 || k >= MAX_LISTENERS_PER_EVENT) {
                        printf("Error: Invalid listener function index %d\n", k);
                        continue;
                    }
                    
                    if (eventListeners[j].listeners[k] != NULL) {
                        eventListeners[j].listeners[k](event);
                    }
                }
            }
        }

        EventData_Free(&event); 
        eventQueue[i] = (Event){0};  // Réinitialiser l'événement après traitement
    }
    eventQueueCount = 0;
}

void updateEvent() {
    SDL_Event sdlEvent;
    static int mouse_x = 0, mouse_y = 0; 
    static bool leftMouseHeld = false;
    static bool rightMouseHeld = false;
    static bool middleMouseHeld = false;

    static Uint32 lastLeftClickTime = 0;
    static Uint32 lastRightClickTime = 0;
    Uint32 lastMiddleClickTime = 0;
    static const Uint32 clickThreshold = 100;

    int leftMouseClickType = getEventTypeIndex("EVENT_LEFT_MOUSECLICK");
    int rightMouseClickType = getEventTypeIndex("EVENT_RIGHT_MOUSECLICK");
    int middleMouseClickType = getEventTypeIndex("EVENT_MIDDLE_MOUSECLICK");
    int leftMouseHeldType = getEventTypeIndex("EVENT_LEFT_MOUSEHELD");
    int rightMouseHeldType = getEventTypeIndex("EVENT_RIGHT_MOUSEHELD");
    int middleMouseHeldType = getEventTypeIndex("EVENT_MIDDLE_MOUSEHELD");

    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            changeState(STATE_EXIT);
        }

        Uint32 currentTime = SDL_GetTicks(); 

        if (sdlEvent.type == SDL_MOUSEBUTTONDOWN) {
            SDL_GetMouseState(&mouse_x, &mouse_y);
            SDL_Point* cursor_position = (SDL_Point*)malloc(sizeof(SDL_Point));
            if (cursor_position == NULL) {
                printf("Error: Failed to allocate memory for cursor position\n");
                continue; // Skip this event
            }

            cursor_position->x = mouse_x;
            cursor_position->y = mouse_y;

            Event event = {0};
            event.data = malloc(sizeof(*cursor_position)); // Alloue de la mémoire pour une copie de cursor_position
            if (event.data == NULL) {
                continue;
            }

            // Copier les données de cursor_position vers event.data
            memcpy(event.data, cursor_position, sizeof(*cursor_position));

            if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
                leftMouseHeld = true;
                if (currentTime - lastLeftClickTime > clickThreshold) {
                    event.type.index = leftMouseClickType;
                    strncpy(event.name, "left_click", sizeof(event.name) - 1);
                    lastLeftClickTime = currentTime;
                } else {
                    event.type.index = leftMouseHeldType;
                    strncpy(event.name, "left_held", sizeof(event.name) - 1);
                }
            } else if (sdlEvent.button.button == SDL_BUTTON_RIGHT) {
                rightMouseHeld = true;
                if (currentTime - lastRightClickTime > clickThreshold) {
                    event.type.index = rightMouseClickType;
                    strncpy(event.name, "right_click", sizeof(event.name) - 1);
                    lastRightClickTime = currentTime;
                } else {
                    event.type.index = rightMouseHeldType;
                    strncpy(event.name, "right_held", sizeof(event.name) - 1);
                }
            } else if (sdlEvent.button.button == SDL_BUTTON_MIDDLE) {
                middleMouseHeld = true;
                if (currentTime - lastMiddleClickTime > clickThreshold) {
                    event.type.index = middleMouseClickType;
                    strncpy(event.name, "middle_click", sizeof(event.name) - 1);
                    lastMiddleClickTime = currentTime;
                } else {
                    event.type.index = middleMouseHeldType;
                    strncpy(event.name, "middle_held", sizeof(event.name) - 1);
                }
            }

            emitEvent(event);

        } else if (sdlEvent.type == SDL_MOUSEBUTTONUP) {
            if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
                leftMouseHeld = false;
            } else if (sdlEvent.button.button == SDL_BUTTON_RIGHT) {
                rightMouseHeld = false;
            } else if (sdlEvent.button.button == SDL_BUTTON_MIDDLE) {
                middleMouseHeld = false;
            }
        }

        SDL_Point cursor_position;
        cursor_position.x = mouse_x;
        cursor_position.y = mouse_y;

        if (leftMouseHeld) {
            Event event = {0};
            event.type.index = leftMouseHeldType;
            strncpy(event.name, "left_held", sizeof(event.name) - 1);
            event.data = malloc(sizeof(SDL_Point));
            if (event.data) {
                memcpy(event.data, &cursor_position, sizeof(SDL_Point));
                emitEvent(event);
            }
        }

        if (rightMouseHeld) {
            Event event = {0};
            event.type.index = rightMouseHeldType;
            strncpy(event.name, "right_held", sizeof(event.name) - 1);
            event.data = malloc(sizeof(SDL_Point));
            if (event.data) {
                memcpy(event.data, &cursor_position, sizeof(SDL_Point));
                emitEvent(event);
            }
        }

        if (middleMouseHeld) {
            Event event = {0};
            event.type.index = middleMouseHeldType;
            strncpy(event.name, "middle_held", sizeof(event.name) - 1);
            event.data = malloc(sizeof(SDL_Point));
            if (event.data) {
                memcpy(event.data, &cursor_position, sizeof(SDL_Point));
                emitEvent(event);
            }
        }
    }
}

int getEventTypeIndex(const char* eventName) {
    for (int i = 0; i < eventTypeCount; ++i) {
        if (strcmp(eventTypes[i].name, eventName) == 0) {
            return eventTypes[i].index;
        }
    }
    return -1;  // Renvoie -1 si le type d'événement n'est pas trouvé
}

// Fonction pour récupérer l'index d'un type d'événement par son nom
EventType getEventType(const char* eventName) {
    for (int i = 0; i < eventTypeCount; ++i) {
        if (strcmp(eventTypes[i].name, eventName) == 0) {
            return eventTypes[i];
        }
    }
    return EVENT_NOT_FOUND;
}

// Fonction qui vérifie si le nom d'un événement correspond à une chaîne donnée
bool isEventName(Event event, const char* name) {
    if (strncmp(event.name, name, sizeof(event.name)) == 0) {
        return true;
    }
    return false;
}

// ERREUR ICI
// Fonction pour libérer la mémoire allouée pour TimerData
void EventData_Free(Event *event) {
    if (event->data == NULL || event->name == NULL || event->type.name == NULL) {
        printf("EventData_Free: Event is Corrupted\n");
    }

    if (event->data) {
        free(event->data);
        event->data = NULL;
    }

}
