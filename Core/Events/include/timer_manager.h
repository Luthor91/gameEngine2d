#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include <stddef.h>

#define DEFAULT_TIMER TimerManager_Init()

typedef struct Timer {
    int id;                 ///< Identifiant unique du timer, attribué automatiquement.
    int delay;              ///< Délai en millisecondes avant le premier appel de la fonction callback.
    int start_time;         ///< Temps de départ du timer (en millisecondes depuis le début du programme).
    int repeat;             ///< Indique le nombre de répétitions. Si 0, le timer est non-répétitif.
    void (*callback)(void*);///< Fonction de rappel à appeler lorsque le timer expire.
    void* data;             ///< Données à passer à la fonction de rappel.
    struct Timer* next;     ///< Pointeur vers le timer suivant dans la liste chaînée.
} Timer;

typedef struct TimerManager {
    Timer* head;            ///< Pointeur vers le premier timer de la liste chaînée.
} TimerManager;

extern TimerManager* TIMER_MANAGER;
static int last_timer_id = 0;  // Variable statique pour suivre le dernier identifiant attribué

/**
 * Initialise un TimerManager.
 *
 * @return Un pointeur vers un nouvel objet TimerManager, ou NULL en cas d'échec.
 */
TimerManager* TimerManager_Init();

/**
 * Initialise un Timer avec un identifiant auto-attribué.
 *
 * @param delay Délai en millisecondes avant le premier appel de la fonction callback.
 * @param callback Fonction de rappel à appeler lorsque le timer expire.
 * @param data Données à passer à la fonction de rappel.
 * @param repeat Nombre de répétitions. Si 0, le timer est non-répétitif.
 * @return Un pointeur vers un nouvel objet Timer, ou NULL en cas d'échec.
 */
Timer* Timer_Init(int delay, void (*callback)(void*), void* data, int repeat);

/**
 * Ajoute un nouveau timer à la gestion.
 *
 * @param manager Pointeur vers le TimerManager qui gère les timers.
 * @param timer Pointeur vers le timer à ajouter.
 */
void TimerManager_Add(TimerManager* manager, Timer* timer);

/**
 * Met à jour les timers, appelant les callbacks lorsque les timers expirent.
 *
 * @param manager Pointeur vers le TimerManager à mettre à jour.
 */
void TimerManager_Update(TimerManager* manager);

/**
 * Supprime un timer de la gestion en fonction de son identifiant.
 *
 * @param manager Pointeur vers le TimerManager dont le timer sera supprimé.
 * @param id Identifiant du timer à supprimer.
 */
void TimerManager_RemoveTimer(TimerManager* manager, int id);

#endif // TIMER_MANAGER_H