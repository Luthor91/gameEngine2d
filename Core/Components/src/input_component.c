#include "../include/input_component.h"

static InputComponent inputComponents[MAX_ENTITIES];

InputComponent* getInputComponent(Entity entity) {
    if (entity < MAX_ENTITIES) {
        return &inputComponents[entity];
    }
    return NULL;
}

void addInputComponent(Entity entity, InputComponent input) {
    if (entity < MAX_ENTITIES) {
        inputComponents[entity] = input;
    }
}


bool isActionActive(InputComponent* input, SDL_Keycode key) {
    if (key < MAX_KEYS) {
        return input->keys[key];
    }
    return false;
}