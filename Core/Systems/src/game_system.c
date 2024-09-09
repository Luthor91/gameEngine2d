#include "../include/game_system.h"

// Définition de la variable globale pour l'état actuel du jeu
GameState current_state = STATE_INIT;

// Fonction pour initialiser l'état du jeu
void initStateMachine() {
    current_state = STATE_INIT;
}

// Fonction pour changer l'état du jeu
void changeState(GameState newState) {
    current_state = newState;
}

// Fonction pour gérer l'état actuel
void handleState() {
    switch (current_state) {
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
    float deltaTime = Time_GetDelta();
    
    Uint32 startTime = Time_GetCurrentTime(); // Temps avant l'exécution
    updateEvent();
    updateMovement(deltaTime);
    updateParticles(deltaTime);
    updateCollisionSystem();
    updateTimers(deltaTime);
    processEvents();
    updateAnimations();
    renderEntities();
    cleanupSystem();
    Time_SetFPSLimit(DEFAULT_FPS_HIGH);
}

// Gestion de l'état de pause
void handlePausedState() {
}

// Gestion de l'état de fin de jeu
void handleGameOverState() {
    // Provisoire
    changeState(STATE_EXIT);
}

void handleExitState() {
    for (Entity entity = 0; entity < getEntityCount(); ++entity) {
        entityStates[entity] = false;
        hasSprite[entity] = false;
        hasPosition[entity] = false;
        hasVelocity[entity] = false;
        hasInput[entity] = false;
        hasTransform[entity] = false;
        hasAnimation[entity] = false;
        hasHitbox[entity] = false;
        hasSize[entity] = false;
        hasTags[entity] = false;

        SDL_Texture* texture = getSpriteComponent(entity)->texture;
        if (texture != NULL) {
            SDL_DestroyTexture(texture);
        }
    }

    freeParticleEmitters(getEmitters(), MAX_EMITTERS);
    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);
    SDL_Quit();

}