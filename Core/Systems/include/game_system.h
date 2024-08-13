#ifndef GAME_SYSTEM_H
#define GAME_SYSTEM_H

#include <stdbool.h>
#include "../../core.h"

// Liste des états possibles
typedef enum GameState {
    STATE_INIT,        // État d'initialisation
    STATE_MENU,        // État du menu principal
    STATE_PLAYING,     // État de jeu
    STATE_PAUSED,      // État de pause
    STATE_GAME_OVER,   // État de fin de jeu
    STATE_EXIT         // État de sortie du jeu
} GameState;

// Variable globale pour suivre l'état actuel du jeu
extern GameState currentState;

// Fonction pour initialiser l'état du jeu
void initStateMachine();

// Fonction pour changer l'état du jeu
void changeState(GameState newState);

// Fonction pour gérer l'état actuel
void handleState();

// Fonctions pour les différents états (optionnelles)
void handleInitState();
void handleMenuState();
void handlePlayingState();
void handlePausedState();
void handleGameOverState();
void handleExitState();

#endif
