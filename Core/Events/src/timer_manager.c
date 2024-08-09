#include "../include/timer_manager.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

TimerManager* TIMER_MANAGER = NULL;

TimerManager* TimerManager_Init() {
    TimerManager* manager = (TimerManager*)malloc(sizeof(TimerManager));
    manager->head = NULL;
    return manager;
}

Timer* Timer_Init(int delay, void (*callback)(void*), void* data, int repeat) {
    Timer* new_timer = (Timer*)malloc(sizeof(Timer));
    if (new_timer == NULL) return NULL;

    new_timer->id = ++last_timer_id;  // Attribuer un nouvel identifiant unique
    new_timer->delay = delay;
    new_timer->start_time = SDL_GetTicks();
    new_timer->callback = callback;
    new_timer->data = data;
    new_timer->repeat = repeat;
    new_timer->next = NULL;

    return new_timer;
}

void TimerManager_Add(TimerManager* manager, Timer* timer) {
    if (manager == NULL ) {
        printf("TimerManager_Add: manager is NULL\n");
        return;
    }
    if (timer == NULL ) {
        printf("TimerManager_Add: timer is NULL\n");
        return;
    }
    
    timer->next = manager->head;
    manager->head = timer;
}

void TimerManager_Update(TimerManager* manager) {
    
    if (manager == NULL || manager->head == NULL) { return; }

    int current_time = SDL_GetTicks();
    Timer* timer = manager->head;
    Timer* prev = NULL;
    
    while (timer != NULL) {
        if (current_time - timer->start_time >= timer->delay) {
            timer->callback(timer->data);

            if (timer->repeat) {
                timer->start_time = current_time;
                prev = timer;
                timer = timer->next;
            } else {
                if (prev == NULL) {
                    manager->head = timer->next;
                } else {
                    prev->next = timer->next;
                }
                Timer* to_free = timer;
                timer = timer->next;
                free(to_free);
            }
        } else {
            prev = timer;
            timer = timer->next;
        }
    }
}

void TimerManager_RemoveTimer(TimerManager* manager, int id) {
    Timer* timer = manager->head;
    Timer* prev = NULL;

    while (timer != NULL) {
        if (timer->id == id) {
            if (prev == NULL) {
                manager->head = timer->next;
            } else {
                prev->next = timer->next;
            }
            free(timer);
            return;
        }
        prev = timer;
        timer = timer->next;
    }
}