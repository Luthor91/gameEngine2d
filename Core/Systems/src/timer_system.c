#include "../include/timer_system.h"

// Tableau de composants timer pour chaque entité
static TimerComponent timerComponents[MAX_ENTITIES][MAX_TIMERS_PER_ENTITY];

TimerData* TimerData_Init(const char* name, Entity entity) {
    TimerData* timer = (TimerData*)malloc(sizeof(TimerData));
    if (timer == NULL) {
        printf("Memory allocation failed for TimerData\n");
        return NULL;
    }

    // Allouer de la mémoire pour le nom du timer
    timer->name = (char*)malloc(MAX_TIMER_NAME_LENGTH * sizeof(char));
    if (timer->name == NULL) {
        printf("Memory allocation failed for timer name\n");
        free(timer);  // Libérer la mémoire allouée pour TimerData
        return NULL;
    }

    // Copier le nom dans la mémoire allouée
    strncpy(timer->name, name, MAX_TIMER_NAME_LENGTH - 1);
    timer->name[MAX_TIMER_NAME_LENGTH - 1] = '\0'; // Assurez-vous que le nom est null-terminated

    timer->entity = entity;

    return timer;
}

void addTimerComponent(Entity entity, const char* name, float duration, bool repeat) {
    if (entity >= MAX_ENTITIES) {
        printf("Error: Entity ID out of bounds.\n");
        return;
    }

    for (int i = 0; i < MAX_TIMERS_PER_ENTITY; ++i) {
        TimerComponent* timer = &timerComponents[entity][i];

        // Ajouter un nouveau timer à la première position libre
        if (!timer->active) {
            strncpy(timer->name, name, MAX_TIMER_NAME_LENGTH - 1);
            timer->name[MAX_TIMER_NAME_LENGTH - 1] = '\0'; // Assurez-vous que le nom est null-terminated
            timer->duration = duration;
            timer->elapsedTime = 0.0f;
            timer->active = true;
            timer->repeat = repeat;
            return;
        }
    }

    printf("Error: No available timer slots for entity %u.\n", entity);
}

// Fonction pour mettre à jour tous les timers
void updateTimers(float deltaTime) {
    for (Entity entity = 0; entity < getEntityCount(); ++entity) {
        if (!hasTimerComponent(entity)) continue;

        for (int i = 0; i < MAX_TIMERS_PER_ENTITY; ++i) {
            TimerComponent* timer = &timerComponents[entity][i];
            if (timer->active) {
                // Accumuler le temps écoulé
                timer->elapsedTime += deltaTime;
                // Vérifier si le timer a expiré
                while (timer->elapsedTime >= timer->duration) {
                    // Émettre un événement de type EVENT_TIMER
                    TimerData* timer_data = TimerData_Init(timer->name, entity);
                    Event timerEvent = { getEventType("EVENT_TIMER_EXPIRED"), timer_data };
                    emitEvent(timerEvent);

                    // Réinitialiser le timer
                    timer->elapsedTime -= timer->duration; // Réduire le temps écoulé par la durée du timer
                    if (!timer->repeat) {
                        timer->active = false;
                    }
                }
            }
        }
    }
}

// Fonction pour vérifier si une entité a un TimerComponent actif
int hasTimerComponent(Entity entity) {
    if (entity >= MAX_ENTITIES) {
        return 0;
    }

    for (int i = 0; i < MAX_TIMERS_PER_ENTITY; ++i) {
        if (timerComponents[entity][i].active) {
            return 1;
        }
    }
    return 0;
}

// Fonction pour désactiver un TimerComponent spécifique attaché à une entité
void removeTimerComponent(Entity entity, const char* name) {
    if (entity >= MAX_ENTITIES) {
        return;
    }

    for (int i = 0; i < MAX_TIMERS_PER_ENTITY; ++i) {
        TimerComponent* timer = &timerComponents[entity][i];
        if (timer->active && strcmp(timer->name, name) == 0) {
            timer->active = false;
            return;
        }
    }
}

// Fonction pour obtenir un TimerComponent spécifique attaché à une entité
TimerComponent* getTimerComponent(Entity entity, int index) {
    if (entity >= MAX_ENTITIES || index >= MAX_TIMERS_PER_ENTITY) {
        return NULL;
    }
    
    return &timerComponents[entity][index];
}

TimerComponent* getTimerComponentByName(Entity entity, const char* name) {
    if (entity >= MAX_ENTITIES || name == NULL) {
        return NULL;
    }

    for (int i = 0; i < MAX_TIMERS_PER_ENTITY; ++i) {
        TimerComponent* timer = &timerComponents[entity][i];
        if (timer->active && strcmp(timer->name, name) == 0) {
            return timer;
        }
    }

    return NULL;
}

bool CheckTimerName(Event event, const char* name) {
    if (event.data == NULL) {
        printf("Error: event.data is NULL\n");
        return false;
    }

    TimerData* timer_data = (TimerData*)event.data;
    if (timer_data == NULL) {
        printf("Error: Failed to cast event.data to TimerData*\n");
        return false;
    }

    if (strcmp(timer_data->name, name) == 0) return true;

    return false;
}