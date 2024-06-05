#include "../include/timer_manager.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

TimerManager* TimerManager_Init() {
    TimerManager* manager = (TimerManager*)malloc(sizeof(TimerManager));
    manager->head = NULL;
    return manager;
}

void TimerManager_AddTimer(TimerManager* manager, int id, int delay, void (*callback)(void*), void* data, int repeat) {
    Timer* new_timer = (Timer*)malloc(sizeof(Timer));
    new_timer->id = id;
    new_timer->delay = delay;
    new_timer->start_time = SDL_GetTicks();
    new_timer->callback = callback;
    new_timer->data = data;
    new_timer->repeat = repeat;
    new_timer->next = manager->head;
    manager->head = new_timer;
}

void TimerManager_Update(TimerManager* manager) {
    int current_time = SDL_GetTicks();
    Timer* timer = manager->head;
    Timer* prev = NULL;

    while (timer != NULL) {
        printf("curr : %d, total : %d\n", current_time - timer->start_time, timer->delay);
        if (current_time - timer->start_time >= timer->delay) {
            timer->callback(timer->data);
            if (timer->repeat) {
                timer->start_time = current_time;
                prev = timer;
                timer = timer->next;
            } else {
                if (prev == NULL) {
                    manager->head = timer->next;
                    free(timer);
                    timer = manager->head;
                } else {
                    prev->next = timer->next;
                    free(timer);
                    timer = prev->next;
                }
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
