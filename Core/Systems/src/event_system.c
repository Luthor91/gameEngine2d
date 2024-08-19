#include "../include/event_system.h"

// Variables globales pour gérer les événements
static EventBinding entityBindings[MAX_ENTITIES][MAX_BINDINGS] = {0};
static EventListeners eventListeners[MAX_EVENTS];
static Event eventQueue[MAX_EVENTS];
static int eventQueueCount = 0;
static int listenerCount = 0;

// Ajout d'un écouteur d'événements
void addEventListener(EventType type, EventListener listener) {     
    for (int i = 0; i < MAX_EVENTS; ++i) {
        if (eventListeners[i].type == type) {
            if (eventListeners[i].listenerCount < MAX_LISTENERS) {
                eventListeners[i].listeners[eventListeners[i].listenerCount++] = listener;
                printf("Listener added for event type %d\n", type);
            } else {
                printf("Max listeners reached for event type %d\n", type);
            }
            return;
        } else if (eventListeners[i].listenerCount == 0) {
            eventListeners[i].type = type;
            eventListeners[i].listeners[0] = listener;
            eventListeners[i].listenerCount = 1;
            listenerCount++;
            printf("Listener added for new event type %d\n", type);
            return;
        }
    }
}

// Retrait d'un écouteur d'événements
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

// Émettre un événement
void emitEvent(Event event) {
    if (eventQueueCount < MAX_EVENTS) {
        eventQueue[eventQueueCount++] = event;
        //printf("Event emitted with type: %d\n", event.type);
    } else {
        printf("Event queue is full, cannot emit event of type %d\n", event.type);
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

        if (event.type < 0 || event.type >= MAX_EVENT_TYPE_COUNT) {
            printf("Error: Invalid event type %d\n", event.type);
            continue;
        }

        for (int j = 0; j < listenerCount; ++j) {  // Correction: '<' instead of '<='
            if (j < 0 || j >= MAX_LISTENER_COUNT) {
                printf("Error: Invalid listener index %d\n", j);
                continue;
            }

            if (eventListeners[j].type == event.type) {
                for (int k = 0; k < eventListeners[j].listenerCount; ++k) {  // Correction: '<' instead of '<='
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
    }
    eventQueueCount = 0;  // Réinitialiser la file d'attente des événements
}

// Met à jour les événements et émet les événements liés aux touches
void updateEvent() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            changeState(STATE_EXIT);
        }      
        bool eventHandled = false; 

        if (sdlEvent.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            // Créer l'événement de tir
            SDL_Point* cursorPos = (SDL_Point*)malloc(sizeof(SDL_Point));
            cursorPos->x = mouseX;
            cursorPos->y = mouseY;
            if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
                Event clickEvent = {EVENT_TYPE_LEFT_MOUSECLICK, cursorPos};
                emitEvent(clickEvent);
            } else if (sdlEvent.button.button == SDL_BUTTON_RIGHT) {
                Event clickEvent = {EVENT_TYPE_RIGHT_MOUSECLICK, cursorPos};
                emitEvent(clickEvent);
            } else if (sdlEvent.button.button == SDL_BUTTON_MIDDLE) {
                Event clickEvent = {EVENT_TYPE_MIDDLE_MOUSECLICK, cursorPos};
                emitEvent(clickEvent);
            }
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
