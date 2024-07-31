#ifndef TIME_H
#define TIME_H

#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>

#define FPS_CALC_INTERVAL 1000
#define DEFAULT_FPS_AVERAGE 60

/**
 * @brief Initialise les variables de temps.
 * 
 * @param current_time Pointeur vers la variable contenant le temps actuel.
 * @param previous_time Pointeur vers la variable contenant le temps précédent.
 */
void Time_Initialize(Uint32* current_time, Uint32* previous_time);

/**
 * @brief Met à jour le delta time entre deux cadres.
 * 
 * @param current_time Pointeur vers la variable contenant le temps actuel.
 * @param previous_time Pointeur vers la variable contenant le temps précédent.
 * @return float Le delta time calculé.
 */
float Time_UpdateDeltaTime(Uint32* current_time, Uint32* previous_time);

/**
 * @brief Obtient le temps actuel.
 * 
 * @return Uint32 Le temps actuel en millisecondes.
 */
Uint32 Time_GetCurrentTime();

/**
 * @brief Calcule le delta time entre deux temps donnés.
 * 
 * @param current_time Le temps actuel.
 * @param previous_time Le temps précédent.
 * @return float Le delta time calculé en secondes.
 */
float Time_CalculateDeltaTime(Uint32 current_time, Uint32 previous_time);

/**
 * @brief Met le programme en pause pendant un certain nombre de millisecondes.
 * 
 * @param milliseconds Le nombre de millisecondes pendant lesquelles le programme doit être en pause.
 */
void Time_Sleep(unsigned int milliseconds);

/**
 * @brief Définit une limite d'images par seconde (FPS).
 * 
 * @param fps La limite d'images par seconde.
 */
void Time_SetFPSLimit(float fps);

/**
 * @brief Obtient un timestamp actuel sous forme de chaîne de caractères.
 * 
 * @return char* Un timestamp sous forme de chaîne de caractères. 
 *         L'appelant est responsable de libérer cette mémoire.
 */
char* Time_GetTimeStamp();

/**
 * @brief Obtient le nombre d'images par seconde (FPS) actuel.
 * 
 * @return float Le nombre d'images par seconde (FPS) actuel.
 */
float Time_GetFPS();

#endif /* TIME_H */
