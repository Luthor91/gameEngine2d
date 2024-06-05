// gcc -I/usr/include/SDL2 -o timer_test Examples/SDL2/timer_test.c Core/Events/src/timer_manager.c -lSDL2 -lSDL2_image -lm && ./timer_test

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>

#include "../../Core/Events/include/timer_manager.h"

void MyCallbackFunction(void* data) {
    printf("Timer expired!\n\tData : %c\n", data);
}

int main() {
    SDL_Init(SDL_INIT_TIMER);
    
    TimerManager* manager = TimerManager_Init();
    
    TimerManager_AddTimer(manager, 1, 100, MyCallbackFunction, (void*)'A', 1);
    TimerManager_AddTimer(manager, 2, 250, MyCallbackFunction, (void*)'B', 1);
    TimerManager_AddTimer(manager, 3, 500, MyCallbackFunction, (void*)'C', 1);
    TimerManager_AddTimer(manager, 4, 750, MyCallbackFunction, (void*)'D', 1);
    TimerManager_AddTimer(manager, 5, 1250, MyCallbackFunction, (void*)'E', 1);
    TimerManager_AddTimer(manager, 6, 1500, MyCallbackFunction, (void*)'F', 1);
    TimerManager_AddTimer(manager, 7, 1750, MyCallbackFunction, (void*)'G', 1);
    TimerManager_AddTimer(manager, 8, 2000, MyCallbackFunction, (void*)'H', 1);
    TimerManager_AddTimer(manager, 9, 2500, MyCallbackFunction, (void*)'I', 1);
    TimerManager_AddTimer(manager, 10, 3000, MyCallbackFunction, (void*)'J', 1);
    
    while (1) {
        TimerManager_Update(manager);
        SDL_Delay(60/1000);  // Attendre un peu pour éviter une boucle serrée
    }
    
    SDL_Quit();
    return 0;
}