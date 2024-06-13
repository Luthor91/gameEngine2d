#include "../include/time.h"

// Initialisation des variables de temps
void Time_Initialize(Uint32* current_time, Uint32* previous_time) {
    *current_time = Time_GetCurrentTime();
    *previous_time = *current_time;
}

// Mise à jour de deltaTime
float Time_UpdateDeltaTime(Uint32* current_time, Uint32* previous_time) {
    *current_time = Time_GetCurrentTime();
    float deltaTime = Time_CalculateDeltaTime(*current_time, *previous_time);
    *previous_time = *current_time;
    return deltaTime;
}

Uint32 Time_GetCurrentTime() {
    return SDL_GetTicks();
}

float Time_CalculateDeltaTime(Uint32 current_time, Uint32 previous_time) {
    return (current_time - previous_time) / 1000.0f;
}

void Time_Sleep(unsigned int milliseconds) {
    SDL_Delay(milliseconds);
}

void Time_SetFPSLimit(int fps) {
    int delay_time = 1000 / fps;
    SDL_Delay(delay_time);
}

char* Time_GetTimeStamp() {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char *time_stamp = asctime(tm_info);
    // Supprimer le saut de ligne final
    time_stamp[strlen(time_stamp) - 1] = '\0';
    return time_stamp;
}
