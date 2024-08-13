#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "../../Entities/include/entity.h"

#define MAX_KEYS 512 // Taille arbitraire pour couvrir toutes les touches SDL
#define INPUT_EMPTY {{false}}

typedef struct InputComponent {
    bool keys[MAX_KEYS]; // Tableau pour stocker l'état des touches
} InputComponent;

static InputComponent inputComponents[MAX_ENTITIES];

InputComponent* getInputComponent(Entity entity);
void addInputComponent(Entity entity, InputComponent input);
bool isActionActive(InputComponent* input, SDL_Keycode key);

#endif
