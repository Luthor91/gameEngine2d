#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "../../UI/include/window.h"
#include "../../Utilities/include/time.h"

#define MAX_LINE_LENGTH 1024

/**
 * @brief Initialise l'environnement à partir d'un fichier de configuration.
 * 
 * @param filename Le chemin du fichier de configuration.
 */
void Init_Env(const char *filename);

/**
 * @brief Initialise toutes les bibliothèques nécessaires pour l'application.
 * 
 * @return int Retourne 0 si l'initialisation est réussie, sinon retourne une valeur négative indiquant l'erreur.
 */
int Init_All();

/**
 * @brief Ferme et libère toutes les ressources allouées, y compris la fenêtre.
 * 
 * @param window Pointeur vers la structure Window à fermer et libérer.
 */
void Exit_All(Window* window);

#endif // INIT_H
