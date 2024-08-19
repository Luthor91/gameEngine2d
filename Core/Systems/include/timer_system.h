#ifndef TIMER_SYSTEM_H
#define TIMER_SYSTEM_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../Entities/include/entity.h"
#include "../../Systems/include/event_system.h"

// Limite de timers par entité
#define MAX_TIMERS_PER_ENTITY 32
#define MAX_TIMER_NAME_LENGTH 32

// Définir un type pour la fonction de callback
typedef void (*CallbackFunction)(void*);

// Structure du composant Timer
typedef struct TimerComponent {
    char name[MAX_TIMER_NAME_LENGTH];      // Nom du timer
    float duration;     // Durée du timer
    float elapsedTime;  // Temps écoulé
    bool active;        // 1 si le timer est actif, 0 sinon
    bool repeat;        // 1 si le timer doit se répéter, 0 sinon
} TimerComponent;

// Structure contenant les données associées à un timer
typedef struct TimerData {
    Entity entity;   // L'entité à laquelle le timer est attaché
    char* name;      // Nom du timer
} TimerData;

// Fonction pour initialiser le système de timers
TimerData* TimerData_Init(const char* name, Entity entity);

// Fonction pour ajouter un composant Timer à une entité
void addTimerComponent(Entity entity, const char* name, float duration, bool repeat);

// Fonction pour mettre à jour tous les timers
void updateTimers(float deltaTime);

// Fonction pour vérifier si une entité a un TimerComponent actif
int hasTimerComponent(Entity entity);

// Fonction pour désactiver un TimerComponent spécifique attaché à une entité
void removeTimerComponent(Entity entity, const char* name);

// Fonction pour obtenir un TimerComponent spécifique attaché à une entité
TimerComponent* getTimerComponent(Entity entity, int index);

// Fonction pour obtenir un TimerComponent spécifique attaché à une entité par son nom
TimerComponent* getTimerComponentByName(Entity entity, const char* name);

// Fonction pour exécuter une fonction après X secondes
void addDelayedFunction(Entity entity, float delay, CallbackFunction callback, void* context);

bool CheckTimerName(Event event, const char* name);

#endif // TIMER_SYSTEM_H
