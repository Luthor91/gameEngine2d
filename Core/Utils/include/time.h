#ifndef TIME_H
#define TIME_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FPS_CALC_INTERVAL 1000
#define DEFAULT_FPS_LOW 20
#define DEFAULT_FPS_AVERAGE 60
#define DEFAULT_FPS_HIGH 120
#define TIME_DELTA Time_GetDelta()

// Variables globales pour le suivi du temps
static Uint32 current_time = 0;
static Uint32 previous_time = 0;
static float delta_time = 0.0f;

// Fonction d'initialisation
void Time_Initialize();

// Fonction de mise à jour du delta time
float Time_UpdateDeltaTime();

// Fonction pour obtenir le temps actuel
Uint32 Time_GetCurrentTime();

// Fonction pour calculer le delta time
float Time_CalculateDeltaTime(Uint32 current_time, Uint32 previous_time);

// Fonction pour dormir pendant un certain temps
void Time_Sleep(unsigned int milliseconds);

// Fonction pour limiter les FPS
void Time_SetFPSLimit(float fps);

// Fonction pour obtenir le FPS actuel
float Time_GetFPS();

// Fonction pour obtenir le timestamp actuel
char* Time_GetTimeStamp();

// Fonction pour obtenir le delta time
float Time_GetDelta();

#endif /* TIME_H */
