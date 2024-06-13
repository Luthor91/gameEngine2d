#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

typedef struct Timer {
    int id;
    int delay;
    int start_time;
    int repeat;
    void (*callback)(void*);
    void* data;
    struct Timer* next;
} Timer;

typedef struct TimerManager {
    Timer* head;
} TimerManager;

TimerManager* TimerManager_Init();
void TimerManager_AddTimer(TimerManager* manager, int id, int delay, void (*callback)(void*), void* data, int repeat);
void TimerManager_Update(TimerManager* manager);
void TimerManager_RemoveTimer(TimerManager* manager, int id);

#endif // TIMER_MANAGER_H
