#include "../include/event_manager.h"

void addEventListener(int eventType, void (*callback)(Event event)) {
    if (listenerCount < MAX_EVENT_LISTENERS) {
        eventListeners[listenerCount].eventType = eventType;
        eventListeners[listenerCount].callback = callback;
        listenerCount++;
    }
}

void emitEvent(Event event) {
    if (eventQueueSize < MAX_EVENT_LISTENERS) {
        eventQueue[eventQueueSize++] = event;
    }
}

void processEvents() {
    for (int i = 0; i < eventQueueSize; i++) {
        Event event = eventQueue[i];
        for (int j = 0; j < listenerCount; j++) {
            if (eventListeners[j].eventType == event.type) {
                eventListeners[j].callback(event);
            }
        }
    }
    eventQueueSize = 0;
}

void updateInput() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            Event quitEvent = {EVENT_TYPE_QUIT, NULL};
            emitEvent(quitEvent);
        } else if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP) {
            Event inputEvent;
            inputEvent.type = (sdlEvent.type == SDL_KEYDOWN) ? EVENT_TYPE_KEYDOWN : EVENT_TYPE_KEYUP;
            inputEvent.data = (void*)(intptr_t)sdlEvent.key.keysym.sym;
            emitEvent(inputEvent);
        }
    }
}
