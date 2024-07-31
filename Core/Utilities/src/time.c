#include "../include/time.h"

void Time_Initialize(Uint32* current_time, Uint32* previous_time) {
    *current_time = Time_GetCurrentTime();
    *previous_time = *current_time;
}

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

void Time_SetFPSLimit(float fps) {
    static Uint32 last_time = 0;
    Uint32 current_time, elapsed_time;

    current_time = Time_GetCurrentTime();
    elapsed_time = current_time - last_time;

    // Temps d'attente restant pour atteindre le FPS spécifié
    Uint32 target_delay = 1000 / fps;

    if (elapsed_time < target_delay) {
        Time_Sleep(target_delay - elapsed_time);
    }

    last_time = Time_GetCurrentTime();
}

float Time_GetFPS() {
    static Uint32 frame_count = 0;
    static Uint32 last_time = 0;
    static float fps = 0.0f;

    Uint32 current_time = SDL_GetTicks();
    frame_count++;

    // Vérifier si une seconde s'est écoulée
    if (current_time > last_time + FPS_CALC_INTERVAL) {
        fps = (float)frame_count * 1000.0f / (current_time - last_time);
        last_time = current_time;
        frame_count = 0;
    }

    return fps;
}

char* Time_GetTimeStamp() {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char *time_stamp = asctime(tm_info);
    time_stamp[strlen(time_stamp) - 1] = '\0';
    return time_stamp;
}
