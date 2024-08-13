#include "../include/game_system.h"

// Définition de la variable globale pour l'état actuel du jeu
GameState currentState = STATE_INIT;

// Fonction pour initialiser l'état du jeu
void initStateMachine() {
    currentState = STATE_INIT;
}

// Fonction pour changer l'état du jeu
void changeState(GameState newState) {
    currentState = newState;
}

// Fonction pour gérer l'état actuel
void handleState() {
    switch (currentState) {
        case STATE_INIT:
            handleInitState();
            break;
        case STATE_MENU:
            handleMenuState();
            break;
        case STATE_PLAYING:
            handlePlayingState();
            break;
        case STATE_PAUSED:
            handlePausedState();
            break;
        case STATE_GAME_OVER:
            handleGameOverState();
            break;
        case STATE_EXIT:
            handleExitState();
            break;
        default:
            break;
    }
}

// Gestion de l'état d'initialisation
void handleInitState() {
    changeState(STATE_MENU);
}

// Gestion de l'état du menu principal
void handleMenuState() {
}

// Gestion de l'état de jeu
void handlePlayingState() {
    updateEvent();
    processEvents();
    updateMovement();
    updateCollisionSystem()
    updateAnimations();
    renderEntities();
    Time_SetFPSLimit(DEFAULT_FPS_HIGH);
}

// Gestion de l'état de pause
void handlePausedState() {
}

// Gestion de l'état de fin de jeu
void handleGameOverState() {
}

void handleExitState() {
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
        entityStates[entity] = false;
        hasSprite[entity] = false;
        hasPosition[entity] = false;
        hasVelocity[entity] = false;
        hasInput[entity] = false;
        hasTransform[entity] = false;
        hasAnimation[entity] = false;

        if (spriteComponents[entity].texture != NULL) {
            SDL_DestroyTexture(spriteComponents[entity].texture);
        }
        
    }
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    SDL_Quit();

}