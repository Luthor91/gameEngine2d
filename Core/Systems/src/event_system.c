#include "../include/event_system.h"
#include <SDL2/SDL.h>

// Ajout d'un écouteur d'événements
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
            listenerCount++;  // Ajouté pour suivre le nombre total de types d'événements
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

// Traiter les événements en file d'attente
void processEvents() {
    if (eventQueueCount == 0) { return; }

    for (int i = 0; i < eventQueueCount; ++i) {
        Event event = eventQueue[i];

        for (int j = 0; j <= listenerCount; ++j) {
            if (eventListeners[j].type == event.type) {
                for (int k = 0; k < eventListeners[j].listenerCount; ++k) {
                    if (eventListeners[j].listeners[k] != NULL) {
                        eventListeners[j].listeners[k](event);
                    }
                }
            }
        }
    }

    // Réinitialise la queue après le traitement
    eventQueueCount = 0;
}

// Met à jour les événements et émet les événements liés aux touches
void updateEvent() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }

        // Gestion des clics de souris pour émettre un événement de tir
        if (sdlEvent.type == SDL_MOUSEBUTTONDOWN) {
            if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Créer l'événement de tir
                SDL_Point* cursorPos = (SDL_Point*)malloc(sizeof(SDL_Point));
                cursorPos->x = mouseX;
                cursorPos->y = mouseY;
                Event shootEvent = {EVENT_TYPE_SHOOT, cursorPos};
                emitEvent(shootEvent);
            }
        }

        // Gestion des événements clavier
        if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP) {
            bool isPressed = (sdlEvent.type == SDL_KEYDOWN);
            SDL_Keycode key = sdlEvent.key.keysym.sym;

            for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
                if (!hasInput[entity]) { continue; }

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
