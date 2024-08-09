#include "../../Physics/include/impulse.h"
#include <stdlib.h>
#include <stdio.h>

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
    // Allocation mémoire pour ImpulseManager
    ImpulseManager* manager = (ImpulseManager*)malloc(sizeof(ImpulseManager));
    if (manager == NULL) {
        fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire pour ImpulseManager.\n");
        return NULL;
    }

    // Allocation mémoire pour le tableau des impulsions
    manager->impulses = (Impulse**)malloc(max_impulses * sizeof(Impulse*));
    if (manager->impulses == NULL) {
        fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire pour le tableau des impulsions.\n");
        free(manager);
        return NULL;
    }

    // Initialisation des paramètres de ImpulseManager
    manager->max_impulses = max_impulses;
    manager->index = 0;

    // Initialisation des impulsions à NULL
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

void ImpulseManager_Add(ImpulseManager* manager, Impulse* impulse) {
    if (manager == NULL || impulse == NULL) {
        printf("ImpulseManager_Add: manager or impulse NULL\n");
        return;
    }
    if (manager->index < manager->max_impulses) {   
        manager->impulses[manager->index] = impulse;
        manager->index++;
    }
}
