#include "../include/event_system.h"

// Variables globales pour gérer les événements
static EventBinding entityBindings[MAX_ENTITIES][MAX_BINDINGS] = {0};
static EventListeners eventListeners[MAX_EVENTS] = {0};
static Event eventQueue[MAX_EVENTS] = {0};
static int eventQueueCount = 0;
static int listenerCount = 0;

static EventType eventTypes[MAX_EVENT_TYPES] = {0};
static int eventTypeCount = 0;

void initializeEventTypes() {
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
        // Sécuriser la copie de chaîne
        strncpy(eventTypes[eventTypeCount].name, predefinedEventNames[i], sizeof(eventTypes[eventTypeCount].name) - 1);
        eventTypes[eventTypeCount].name[sizeof(eventTypes[eventTypeCount].name) - 1] = '\0';
        eventTypes[eventTypeCount].index = eventTypeCount;
        eventTypeCount++;
    }
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
            entityBindings[entity][i].eventType = (EventType){0};

            // Libérer la mémoire associée à eventData si elle est allouée dynamiquement
            if (entityBindings[entity][i].eventData != NULL) {
                free(entityBindings[entity][i].eventData);
                entityBindings[entity][i].eventData = NULL;
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

void bindEvent(Entity entity, SDL_Keycode key, EventType eventType, void* eventData) {
    for (int i = 0; i < MAX_BINDINGS; ++i) {
        if (entityBindings[entity][i].key == key || entityBindings[entity][i].key == 0) {
            entityBindings[entity][i].key = key;
            entityBindings[entity][i].eventType = eventType;
            entityBindings[entity][i].eventData = eventData;
            return;
        }
    }
    printf("Warning: Max bindings reached for entity %d\n", entity);
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

        // Libérer les données associées à l'événement si elles ont été allouées dynamiquement
        if (event.data != NULL) {
            free(event.data);
            event.data = NULL;
        }

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

    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            changeState(STATE_EXIT);
        }

        int leftMouseClickType = getEventTypeIndex("EVENT_LEFT_MOUSECLICK");
        int rightMouseClickType = getEventTypeIndex("EVENT_RIGHT_MOUSECLICK");
        int middleMouseClickType = getEventTypeIndex("EVENT_MIDDLE_MOUSECLICK");
        int leftMouseHeldType = getEventTypeIndex("EVENT_LEFT_MOUSEHELD");
        int rightMouseHeldType = getEventTypeIndex("EVENT_RIGHT_MOUSEHELD");
        int middleMouseHeldType = getEventTypeIndex("EVENT_MIDDLE_MOUSEHELD");

        Uint32 currentTime = SDL_GetTicks(); 

        if (sdlEvent.type == SDL_MOUSEBUTTONDOWN) {
            SDL_GetMouseState(&mouse_x, &mouse_y);
            SDL_Point* cursor_position = (SDL_Point*)malloc(sizeof(SDL_Point));
            if (!cursor_position) {
                printf("Error: Failed to allocate memory for cursor position\n");
                continue; // Skip this event
            }

            cursor_position->x = mouse_x;
            cursor_position->y = mouse_y;

            Event event = {0};
            event.data = cursor_position; 

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
            free(cursor_position);  // Libérer la mémoire après utilisation
        } else if (sdlEvent.type == SDL_MOUSEBUTTONUP) {
            if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
                leftMouseHeld = false;
            } else if (sdlEvent.button.button == SDL_BUTTON_RIGHT) {
                rightMouseHeld = false;
            } else if (sdlEvent.button.button == SDL_BUTTON_MIDDLE) {
                middleMouseHeld = false;
            }
        }

        // Traitement des événements de souris maintenus
        if (leftMouseHeld) {
            SDL_Point* cursor_position = (SDL_Point*)malloc(sizeof(SDL_Point));
            if (!cursor_position) {
                printf("Error: Failed to allocate memory for cursor position\n");
                continue;
            }

            cursor_position->x = mouse_x;
            cursor_position->y = mouse_y;

            Event event = {0};
            event.type.index = leftMouseHeldType;
            strncpy(event.name, "left_held", sizeof(event.name) - 1);
            event.data = cursor_position; 

            emitEvent(event);
            free(cursor_position);  // Libérer après utilisation
        }

        if (rightMouseHeld) {
            SDL_Point* cursor_position = (SDL_Point*)malloc(sizeof(SDL_Point));
            if (!cursor_position) {
                printf("Error: Failed to allocate memory for cursor position\n");
                continue;
            }

            cursor_position->x = mouse_x;
            cursor_position->y = mouse_y;

            Event event = {0};
            event.type.index = rightMouseHeldType;
            strncpy(event.name, "right_held", sizeof(event.name) - 1);
            event.data = cursor_position; 

            emitEvent(event);
            free(cursor_position);  // Libérer après utilisation
        }

        if (middleMouseHeld) {
            SDL_Point* cursor_position = (SDL_Point*)malloc(sizeof(SDL_Point));
            if (!cursor_position) {
                printf("Error: Failed to allocate memory for cursor position\n");
                continue;
            }

            cursor_position->x = mouse_x;
            cursor_position->y = mouse_y;

            Event event = {0};
            event.type.index = middleMouseHeldType;
            strncpy(event.name, "middle_held", sizeof(event.name) - 1);
            event.data = cursor_position; 

            emitEvent(event);
            free(cursor_position);  // Libérer après utilisation
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