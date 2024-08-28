#include "../include/event_system.h"

// Variables globales pour gérer les événements
static EventBinding entityBindings[MAX_ENTITIES][MAX_BINDINGS] = {0};
static EventListeners eventListeners[MAX_EVENTS];
static Event eventQueue[MAX_EVENTS];
static int eventQueueCount = 0;
static int listenerCount = 0;

static EventType eventTypes[MAX_EVENT_TYPES];
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
        strncpy(eventTypes[eventTypeCount].name, predefinedEventNames[i], sizeof(eventTypes[eventTypeCount].name) - 1);
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

    // Parcours de tous les bindings d'événements pour cette entité
    for (int i = 0; i < MAX_BINDINGS; ++i) {
        // Si un binding est trouvé, le supprimer
        if (entityBindings[entity][i].key != 0) {
            entityBindings[entity][i].key = 0; // Réinitialise la touche liée à cet événement
            entityBindings[entity][i].eventType = (EventType){0}; // Réinitialise le type d'événement
            entityBindings[entity][i].eventData = NULL; // Supprime les données associées à l'événement
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

// Fonction pour lier un événement à une touche
void bindEvent(Entity entity, SDL_Keycode key, EventType eventType, void* eventData) {
    // Trouver le premier binding vide ou mettre à jour un binding existant
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
        eventQueue[i] = (Event){0};
    }
    eventQueueCount = 0;  // Réinitialiser la file d'attente des événements
}

// Met à jour les événements et émet les événements liés aux touches
void updateEvent() {
    SDL_Event sdlEvent;
    static int mouse_x, mouse_y; // Pour garder la position de la souris
    static bool leftMouseHeld = false;
    static bool rightMouseHeld = false;
    static bool middleMouseHeld = false;

    static Uint32 lastLeftClickTime = 0;
    static Uint32 lastRightClickTime = 0;
    static Uint32 lastMiddleClickTime = 0;
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

        Uint32 currentTime = SDL_GetTicks(); // Obtenez le temps actuel en millisecondes

        if (sdlEvent.type == SDL_MOUSEBUTTONDOWN) {
            SDL_GetMouseState(&mouse_x, &mouse_y);
            SDL_Point* cursor_position = (SDL_Point*)malloc(sizeof(SDL_Point));
            cursor_position->x = mouse_x;
            cursor_position->y = mouse_y;

            Event event;
            event.data = cursor_position; // Assignez le pointeur aux données

            if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
                leftMouseHeld = true;
                if (currentTime - lastLeftClickTime > clickThreshold) {
                    event.type.index = leftMouseClickType;
                    emitEvent(event);
                    lastLeftClickTime = currentTime;
                }
            } else if (sdlEvent.button.button == SDL_BUTTON_RIGHT) {
                rightMouseHeld = true;
                if (currentTime - lastRightClickTime > clickThreshold) {
                    event.type.index = rightMouseClickType;
                    emitEvent(event);
                    lastRightClickTime = currentTime;
                }
            } else if (sdlEvent.button.button == SDL_BUTTON_MIDDLE) {
                middleMouseHeld = true;
                if (currentTime - lastMiddleClickTime > clickThreshold) {
                    event.type.index = middleMouseClickType;
                    emitEvent(event);
                    lastMiddleClickTime = currentTime;
                }
            }
        } else if (sdlEvent.type == SDL_MOUSEBUTTONUP) {
            if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
                leftMouseHeld = false;
            } else if (sdlEvent.button.button == SDL_BUTTON_RIGHT) {
                rightMouseHeld = false;
            } else if (sdlEvent.button.button == SDL_BUTTON_MIDDLE) {
                middleMouseHeld = false;
            }
        }
        
        // Émettre des événements de maintien de clic
        if (leftMouseHeld) {
            SDL_GetMouseState(&mouse_x, &mouse_y);
            SDL_Point* cursor_position = (SDL_Point*)malloc(sizeof(SDL_Point));
            cursor_position->x = mouse_x;
            cursor_position->y = mouse_y;
            Event holdEvent = {(EventType){.index = leftMouseHeldType}, cursor_position};
            emitEvent(holdEvent);
        }
        if (rightMouseHeld) {
            SDL_GetMouseState(&mouse_x, &mouse_y);
            SDL_Point* cursor_position = (SDL_Point*)malloc(sizeof(SDL_Point));
            cursor_position->x = mouse_x;
            cursor_position->y = mouse_y;
            Event holdEvent = {(EventType){.index = rightMouseHeldType}, cursor_position};
            emitEvent(holdEvent);
        }
        if (middleMouseHeld) {
            SDL_GetMouseState(&mouse_x, &mouse_y);
            SDL_Point* cursor_position = (SDL_Point*)malloc(sizeof(SDL_Point));
            cursor_position->x = mouse_x;
            cursor_position->y = mouse_y;
            Event holdEvent = {(EventType){.index = middleMouseHeldType}, cursor_position};
            emitEvent(holdEvent);
        }

        // Gestion des événements clavier
        if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP) {
            bool isPressed = (sdlEvent.type == SDL_KEYDOWN);
            SDL_Keycode key = sdlEvent.key.keysym.sym;

            for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
                if (!hasInputComponent(entity)) { continue; }

                InputComponent* input = getInputComponent(entity);
                if (key < MAX_KEYS) {
                    input->keys[key] = isPressed;
                }

                for (int i = 0; i < MAX_BINDINGS; ++i) {
                    if (entityBindings[entity][i].key == key) {
                        Event event = {entityBindings[entity][i].eventType, entityBindings[entity][i].eventData};
                        emitEvent(event);
                    }
                }
            }
        }
    }
}

// Fonction pour ajouter un type d'événement prédéfini
int addEventType(const char* eventName) {
    // Vérifiez si le type existe déjà
    for (int i = 0; i < eventTypeCount; ++i) {
        if (strcmp(eventTypes[i].name, eventName) == 0) {
            return eventTypes[i].index; // Retourne l'index existant
        }
    }

    // Ne pas dépasser la capacité maximale d'événements prédéfinis
    if (eventTypeCount >= MAX_EVENT_TYPES) {
        return -1; // Erreur : nombre maximum de types atteint
    }

    // Ajouter le nouveau type d'événement
    strncpy(eventTypes[eventTypeCount].name, eventName, sizeof(eventTypes[eventTypeCount].name) - 1);
    eventTypes[eventTypeCount].name[sizeof(eventTypes[eventTypeCount].name) - 1] = '\0'; // Assurez-vous que la chaîne est terminée
    eventTypes[eventTypeCount].index = eventTypeCount; // Assigne un nouvel index
    return eventTypes[eventTypeCount++].index;
}


// Fonction pour récupérer l'index d'un type d'événement par son nom
int getEventTypeIndex(const char* eventName) {
    for (int i = 0; i < eventTypeCount; ++i) {
        if (strcmp(eventTypes[i].name, eventName) == 0) {
            return eventTypes[i].index;
        }
    }
    return EVENT_NOT_FOUND_INDEX; // Type non trouvé
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
