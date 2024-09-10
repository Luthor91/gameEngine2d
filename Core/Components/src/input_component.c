#include "../include/input_component.h"

static InputComponent inputComponents[MAX_ENTITIES] = {0};

void addInputComponent(Entity entity, InputComponent input) {
    if (entity < MAX_ENTITIES) {
        inputComponents[entity] = input;
        hasInput[entity] = true;
    }
}

InputComponent* getInputComponent(Entity entity) {
    if (entity < MAX_ENTITIES && hasInput[entity]) {
        return &inputComponents[entity];
    }
    return NULL;
}

bool isActionActive(InputComponent* input, SDL_Keycode key) {
    if (key < MAX_KEYS) {
        return input->keys[key];
    }
    return false;
}