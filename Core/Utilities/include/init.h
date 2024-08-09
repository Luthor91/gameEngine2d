#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "../../UI/include/window.h"
#include "../../Utilities/include/time.h"
#include "../../Events/include/timer_manager.h"
#include "../../Renderer/include/renderer.h"

#include "../../Physics/include/world_physics.h"
#include "../../Physics/include/physicsbodies.h"
#include "../../Physics/include/characterbody.h"
#include "../../Physics/include/rigidbody.h"
#include "../../Physics/include/staticbody.h"

#include "../../Events/include/event_manager.h"
#include "../../Events/include/signal_manager.h"
#include "../../Events/include/timer_manager.h"

#define MAX_LINE_LENGTH 1024

/**
 * @brief Initialise toutes les bibliothèques nécessaires pour l'application.
 * 
 * @return int Retourne 1 si l'initialisation est réussie, sinon retourne une valeur négative indiquant l'erreur.
 */
int Init_All();

void Init_Env(const char *filename);
int Init_Dependancies();
void Init_Global();

/**
 * @brief Ferme et libère toutes les ressources allouées, y compris la fenêtre.
 * 
 * @param window Pointeur vers la structure Window à fermer et libérer.
 */
void Exit_All(Window* window);

#endif // INIT_H
