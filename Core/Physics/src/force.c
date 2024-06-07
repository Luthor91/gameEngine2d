#include "../../Physics/include/force.h"
#include <stdlib.h>

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
    if (manager->index < manager->max_force) {
        manager->forces[manager->index] = force;
        manager->index++;
    }
}

Force* ForceManager_CalculateNetForce(ForceManager* manager) {
    // Initialiser la force nette avec une magnitude nulle
    float netMagnitude = 0.0f;
    float netDirectionX = 0.0f;
    float netDirectionY = 0.0f;

    // Calculer la somme des forces en tenant compte de leur direction et magnitude
    for (int i = 0; i < manager->index; i++) {
        float magnitude = manager->forces[i]->magnitude;
        float direction = manager->forces[i]->direction;
        netMagnitude += magnitude;
        netDirectionX += magnitude * cos(direction); // Calculer les composantes x et y de la direction
        netDirectionY += magnitude * sin(direction);
    }

    // Calculer la direction totale
    float netDirection = atan2(netDirectionY, netDirectionX);

    // Créer et retourner la force nette
    return Force_Init(netMagnitude, netDirection);
}