#include "../../Physics/include/force.h"
#include <stdlib.h>
#include <stdio.h>

Force* Force_Init(float magnitude, float direction) {
    Force* force = (Force*)malloc(sizeof(Force));
    if (force == NULL) {
        return NULL;
    }
    force->magnitude = magnitude;
    force->direction = direction;
    return force;
}

void Force_Destroy(Force* force) {
    free(force);
}

ForceManager* ForceManager_Init(int max_force) {
    ForceManager* manager = (ForceManager*)malloc(sizeof(ForceManager));

    manager->max_force = max_force;
    manager->index = 0;
    manager->forces = (Force**)malloc(max_force * sizeof(Force*));

    for (int i = 0; i < max_force; i++) {
        manager->forces[i] = NULL;
    }
    return manager;
}

void ForceManager_AddForce(ForceManager* manager, Force* force) {
    printf("ForceManager_AddForce index:%d ; max:%d\n", manager->index, manager->max_force);
    if (manager->index < manager->max_force) {
        printf("Force ajouté\n");
        manager->forces[manager->index] = force;
        manager->index++;
    }
}

Force* ForceManager_CalculateNetForce(ForceManager* manager) {
    // Initialiser les composantes x et y de la force nette à zéro
    float netDirectionX = 0.0f;
    float netDirectionY = 0.0f;

    // Calculer la somme des composantes x et y des forces
    for (int i = 0; i < manager->index; i++) {
        printf("ForceManager: Force n°%d\n", i);
        float magnitude = manager->forces[i]->magnitude;
        float direction = manager->forces[i]->direction;
        netDirectionX += magnitude * cos(direction);
        netDirectionY += magnitude * sin(direction);
    }

    // Calculer la magnitude et la direction totale
    float netMagnitude = sqrt(netDirectionX * netDirectionX + netDirectionY * netDirectionY);
    float netDirection = atan2(netDirectionY, netDirectionX);

    // Créer et retourner la force nette
    return Force_Init(netMagnitude, netDirection);
}