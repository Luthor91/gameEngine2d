#include "../include/timer_system.h"

// Tableau de composants timer pour chaque entité
static TimerComponent timerComponents[MAX_ENTITIES][MAX_TIMERS_PER_ENTITY] = { 
    [0 ... MAX_ENTITIES-1] = { 
        [0 ... MAX_TIMERS_PER_ENTITY-1] = { 
            .name = "", 
            .duration = 0.0f, 
            .elapsedTime = 0.0f, 
            .active = false, 
            .repeat = false 
        } 
    } 
};

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
        free(timer);
        timer = NULL;
        return NULL;
    }

    // Copier le nom dans la mémoire allouée
    strncpy(timer->name, name, MAX_TIMER_NAME_LENGTH - 1);
    timer->name[MAX_TIMER_NAME_LENGTH - 1] = '\0'; // Assurez-vous que le nom est null-terminated

    timer->entity = entity;

    return timer;
}

// Fonction pour libérer la mémoire allouée pour TimerData
void TimerData_Free(TimerData* timerData) {
    if (timerData != NULL) {
        if (timerData->name != NULL) {
            free(timerData->name);
            timerData->name = NULL;
        }
        free(timerData);
        timerData = NULL;
    }
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
                    Event timerEvent;
                    timerEvent.type = getEventType("EVENT_TIMER_EXPIRED");
                    timerEvent.data = TimerData_Init(timer->name, entity);
                    strncpy(timerEvent.name, "right_hold", sizeof(timerEvent.name) - 1);  // Nom par défaut "right_hold"
                    timerEvent.name[sizeof(timerEvent.name) - 1] = '\0'; // Assure la terminaison de la chaîne
                    emitEvent(timerEvent);

                    // Libérer la mémoire allouée pour TimerData après émission de l'événement
                    TimerData_Free(timerEvent.data);

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

// Fonction pour désactiver tous les TimerComponent attachés à une entité
void removeAllTimers(Entity entity) {
    if (entity >= MAX_ENTITIES) {
        return;
    }

    for (int i = 0; i < MAX_TIMERS_PER_ENTITY; ++i) {
        TimerComponent* timer = &timerComponents[entity][i];
        if (timer->active) {
            timer->active = false;
        }
    }
}

// Fonction pour désactiver un TimerComponent spécifique attaché à une entité
void removeAllTimersByName(Entity entity, const char* name) {
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
    if (!event.data) {
        printf("Error: event.data is NULL\n");
        return false;
    }

    TimerData* timer_data = (TimerData*)event.data;
    if (!timer_data) {
        printf("Error: TimerData is NULL\n");
        return false;
    }

    if (!timer_data->name) {
        printf("Error: timer_data->name is NULL\n");
        return false;
    }

    // Assurez-vous que name est non NULL et que la comparaison est possible
    if (!name) {
        printf("Error: Comparison name is NULL\n");
        return false;
    }

    if (timer_data->name && name) {
        printf("Comparing timer_data->name='%s' with name='%s'\n", timer_data->name, name);
    }

    return strcmp(timer_data->name, name) == 0;
}