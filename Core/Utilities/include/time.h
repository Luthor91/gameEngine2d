#ifndef TIME_H
#define TIME_H

#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>

// Initialisation des variables de temps
void Time_Initialize(Uint32* current_time, Uint32* previous_time);
// Mise à jour de deltaTime
float Time_UpdateDeltaTime(Uint32* current_time, Uint32* previous_time);

Uint32 Time_GetCurrentTime();
float Time_CalculateDeltaTime(Uint32 current_time, Uint32 previous_time);
void Time_Sleep(unsigned int milliseconds);
void Time_SetFPSLimit(int fps);
char* Time_GetTimeStamp();


#endif /* TIME_H */
