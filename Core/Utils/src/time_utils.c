#include "../include/time_utils.h"

// Initialisation du temps
void Time_Initialize() {
    previous_time = Time_GetCurrentTime();
}

// Mise à jour du delta time
float Time_UpdateDeltaTime() {
    Uint32 current_time = Time_GetCurrentTime();
    delta_time = Time_CalculateDeltaTime(current_time, previous_time);
    previous_time = current_time;
    return delta_time;
}

// Obtention du temps actuel en millisecondes
Uint32 Time_GetCurrentTime() {
    return SDL_GetTicks();
}

// Calcul du delta time
float Time_CalculateDeltaTime(Uint32 current_time, Uint32 previous_time) {
    return (current_time - previous_time) / 1000.0f;
}

// Fonction pour dormir pendant un certain temps
void Time_Sleep(unsigned int milliseconds) {
    SDL_Delay(milliseconds);
}

// Limiter les FPS sans affecter delta_time
void Time_SetFPSLimit(float fps) {
    static Uint32 last_frame_time = 0;
    Uint32 current_time = Time_GetCurrentTime();
    Uint32 frame_duration = 1000 / fps;

    Uint32 elapsed_time = current_time - last_frame_time;

    if (elapsed_time < frame_duration) {
        Time_Sleep(frame_duration - elapsed_time);
    }

    last_frame_time = Time_GetCurrentTime();
}

// Obtenir le FPS actuel
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

// Obtenir le timestamp actuel
char* Time_GetTimeStamp() {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char *time_stamp = asctime(tm_info);
    time_stamp[strlen(time_stamp) - 1] = '\0';
    return time_stamp;
}

// Fonction pour obtenir le delta time
float Time_GetDelta() {
    return Time_UpdateDeltaTime();
}
