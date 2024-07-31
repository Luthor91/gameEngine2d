#include "../../Physics/include/impulse.h"
#include <stdlib.h>

Impulse* Impulse_Init(float magnitude, float direction, float duration) {
    Impulse* impulse = (Impulse*)malloc(sizeof(Impulse));
    if (impulse == NULL) {
        return NULL;
    }
    impulse->magnitude = magnitude;
    impulse->direction = direction;
    impulse->duration = duration;
    impulse->timeElapsed = 0.0f;
    return impulse;
}

void Impulse_Destroy(Impulse* impulse) {
    if (impulse != NULL) {
        free(impulse);
    }
}

ImpulseManager* ImpulseManager_Init(int max_impulses) {
    ImpulseManager* manager = (ImpulseManager*)malloc(sizeof(ImpulseManager));
    if (manager == NULL) {
        return NULL;
    }

    manager->impulses = (Impulse**)malloc(max_impulses * sizeof(Impulse*));
    if (manager->impulses == NULL) {
        free(manager);
        return NULL;
    }

    manager->max_impulses = max_impulses;
    manager->index = 0;

    for (int i = 0; i < max_impulses; i++) {
        manager->impulses[i] = NULL;
    }

    return manager;
}

void ImpulseManager_Destroy(ImpulseManager* manager) {
    if (manager != NULL) {
        for (int i = 0; i < manager->max_impulses; i++) {
            if (manager->impulses[i] != NULL) {
                Impulse_Destroy(manager->impulses[i]);
            }
        }
        free(manager->impulses);
        free(manager);
    }
}

void ImpulseManager_AddImpulse(ImpulseManager* manager, Impulse* impulse) {
    if (manager->index < manager->max_impulses) {
        manager->impulses[manager->index] = impulse;
        manager->index++;
    }
}
