#include "core.h"

void onClick_Print(Event event) {
    printf("clicked\n");
}

void onClick_Exit(Event event) {
    printf("exit\n");
    changeState(STATE_EXIT); 
}

void uponTimerExpired(Event event) {
    if (!CheckTimerName(event, "timer_expired")) return;
    printf("uponTimerExpired\n");
}

int main(int argc, char* argv[]) {
    int init = Init_All();
    if (init == 0) {
        printf("Main: ERROR INIT\n");
    } else {
        printf("Main: Success\n");
    }

    EventType EVENT_LEFT_MOUSECLICK = getEventType("EVENT_LEFT_MOUSECLICK");
    addEventListener(EVENT_LEFT_MOUSECLICK, onClick_Print); 

    EventType EVENT_RIGHT_MOUSECLICK = getEventType("EVENT_RIGHT_MOUSECLICK");
    addEventListener(EVENT_RIGHT_MOUSECLICK, onClick_Exit);   

    EventType EVENT_TIMER_EXPIRED = getEventType("EVENT_TIMER_EXPIRED");
    addEventListener(EVENT_TIMER_EXPIRED, uponTimerExpired);

    player_entity = createEntity();
    addTimerComponent(player_entity, "timer_expired", 1.0f, true);

    Event event_timer = Event_Create(EVENT_TIMER_EXPIRED, "timer_expired");
    event_timer.data = TimerData_Init("timer_expired", player_entity);

    emitEvent(event_timer);

    // Lancement du jeu
    changeState(STATE_PLAYING); 
    while (current_state != STATE_EXIT) {       
        handleState();
    }

    Exit_All();
    
    return 0;
}