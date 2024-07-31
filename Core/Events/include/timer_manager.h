#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

typedef struct Timer {
    int id;                 ///< Identifiant unique du timer.
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

/**
 * Initialise un TimerManager.
 *
 * @return Un pointeur vers un nouvel objet TimerManager, ou NULL en cas d'échec.
 */
TimerManager* TimerManager_Init();

/**
 * Ajoute un nouveau timer à la gestion.
 *
 * @param manager Pointeur vers le TimerManager qui gère les timers.
 * @param id Identifiant unique du timer.
 * @param delay Délai en millisecondes avant le premier appel de la fonction callback.
 * @param callback Fonction de rappel à appeler lorsque le timer expire.
 * @param data Données à passer à la fonction de rappel.
 * @param repeat Nombre de répétitions. Si 0, le timer est non-répétitif.
 */
void TimerManager_AddTimer(TimerManager* manager, int id, int delay, void (*callback)(void*), void* data, int repeat);

/**
 * Met à jour les timers, appelant les callbacks lorsque les timers expirent.
 *
 * @param manager Pointeur vers le TimerManager à mettre à jour.
 */
void TimerManager_Update(TimerManager* manager);

/**
 * Supprime un timer de la gestion.
 *
 * @param manager Pointeur vers le TimerManager dont le timer sera supprimé.
 * @param id Identifiant du timer à supprimer.
 */
void TimerManager_RemoveTimer(TimerManager* manager, int id);

#endif // TIMER_MANAGER_H
