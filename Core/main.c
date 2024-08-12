#include "core.h"

// Dimensions de la fenêtre
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void onMove(Event event) {
    printf("Moving entity with data: %s\n", (char*)event.data);
}

void onJump(Event event) {
    printf("Entity jumping with data: %s\n", (char*)event.data);
}

void onQuit(Event event) {
    printf("Quitting the game\n");
}

int main(int argc, char* argv[]) {
    // Initialiser SDL et créer une fenêtre et un renderer
    SDL_Window* window = createWindow("Game Window");
    SDL_Renderer* renderer = createRenderer(window);

    // Ajouter des listeners pour les événements
    addEventListener(EVENT_TYPE_MOVE, onMove);
    addEventListener(EVENT_TYPE_JUMP, onJump);
    addEventListener(EVENT_TYPE_QUIT, onQuit);

    // Créer une entité
    Entity player = createEntity();

    // Ajouter un InputComponent à l'entité
    InputComponent playerInput = DEFAULT_INPUT;
    addInputComponent(player, playerInput);

    // Ajouter un TransformComponent à l'entité
    TransformComponent playerTransform = DEFAULT_TRANSFORM;
    addTransformComponent(player, playerTransform);

    // Charger une texture pour le SpriteComponent
    SDL_Surface* surface = IMG_Load("Assets/Default/DefaultObject.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Ajouter un SpriteComponent à l'entité
    addSpriteComponent(player, texture, (SDL_Rect){0, 0, 64, 64});

    // Ajouter un AnimationComponent à l'entité (optionnel)
    AnimationComponent playerAnimation = {0, 4, 250, 0}; // 4 frames, 250ms per frame
    addAnimationComponent(player, playerAnimation);

    // Boucle de jeu principale
    bool running = true;
    while (running) {
        // Gérer les entrées
        updateInput();

        // Vérifier les actions et émettre des événements
        InputComponent* input = getInputComponent(player);
        if (input && isActionActive(input, SDLK_w)) {
            Event moveEvent = {EVENT_TYPE_MOVE, "Up"};
            emitEvent(moveEvent);
        } else if (input && isActionActive(input, SDLK_SPACE)) {
            Event jumpEvent = {EVENT_TYPE_JUMP, "Jump"};
            emitEvent(jumpEvent);
        } else if (input && isActionActive(input, SDLK_q)) {
            Event rightEvent = {EVENT_TYPE_MOVE, "Left"};
            emitEvent(rightEvent);
        } else if (input && isActionActive(input, SDLK_d)) {
            Event leftEvent = {EVENT_TYPE_MOVE, "Right"};
            emitEvent(leftEvent);
        }

        // Traiter tous les événements  
        processEvents();

        // Mettre à jour les mouvements, les animations et rendre les entités
        updateMovement(Time_GetDelta());
        updateAnimations();
        renderEntities(renderer);

        // Limit FPS
        Time_SetFPSLimit(60);
    }

    // Nettoyage des ressources SDL
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}