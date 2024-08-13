#include "core.h"

void onClick(Event event) {
    // Création d'une nouvelle entité pour la balle
    Entity bullet = createEntity();
    
    // Récupérer la position du joueur et les dimensions du sprite
    PositionComponent* playerPosition = getPositionComponent(playerEntity);
    SpriteComponent* playerSprite = getSpriteComponent(playerEntity);

    // Calculer le centre du sprite du joueur
    float playerCenterX = playerPosition->x + playerSprite->srcRect.w / 2;
    float playerCenterY = playerPosition->y + playerSprite->srcRect.h / 2;
    
    // Récupérer la position du curseur de la souris
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    
    // Créer une nouvelle composante de position pour la balle
    PositionComponent bulletPosition = {playerCenterX, playerCenterY};
    VelocityComponent bulletVelocity = VELOCITY_ZERO;
    
    // Calculer la direction du tir
    float directionX = mouseX - playerPosition->x;
    float directionY = mouseY - playerPosition->y;
    float length = sqrtf(directionX * directionX + directionY * directionY);
    
    // Normaliser la direction
    if (length != 0) {
        directionX /= length;
        directionY /= length;
    }
    
    // Définir la vitesse de la balle (vitesse ajustable selon vos besoins)
    float bulletSpeed = 200.0f; // Vous pouvez ajuster la vitesse
    bulletVelocity.velocityX = directionX * bulletSpeed;
    bulletVelocity.velocityY = directionY * bulletSpeed;
    
    SDL_Texture* bulletTexture = loadColor(g_renderer, COLOR_BLACK, 12, 12);

    addPositionComponent(bullet, bulletPosition);
    addVelocityComponent(bullet, bulletVelocity);
    addSpriteComponent(bullet, bulletTexture, (SDL_Rect){0, 0, 12, 12});

}

void onMove(Event event) {
    Entity player = playerEntity;
    if (!hasVelocity[player] || player == INVALID_ENTITY_ID) return;
    
    VelocityComponent* velocity = getVelocityComponent(player);
    
    if (strcmp((char*)event.data, "Right") == 0) {
        velocity->velocityX = 50;
        velocity->velocityY = 0;
    } else if (strcmp((char*)event.data, "Left") == 0) {
        velocity->velocityX = -50;
        velocity->velocityY = 0;
    } else if (strcmp((char*)event.data, "Up") == 0) {
        velocity->velocityY = -50;
        velocity->velocityX = 0;
    } else if (strcmp((char*)event.data, "Down") == 0) {
        velocity->velocityY = 50;
        velocity->velocityX = 0;
    }
}

int main(int argc, char* argv[]) {

    Init_All();

    // Ajouter des listeners pour les événements
    addEventListener(EVENT_TYPE_MOVE, onMove);
    addEventListener(EVENT_TYPE_SHOOT, onClick);
    
    Entity background = createEntity();
    PositionComponent backgroundPosition = POSITION_ZERO;  
    SDL_Texture* backgroundTexture = loadColor(g_renderer, COLOR_WHITE, WINDOW_WIDTH, WINDOW_HEIGHT);
    addPositionComponent(background, backgroundPosition);
    addSpriteComponent(background, backgroundTexture, (SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT});

    // Créer une entité et ses composants
    playerEntity = createEntity();
    InputComponent playerInput = INPUT_EMPTY;
    PositionComponent playerPosition = {0, WINDOW_HEIGHT - 64};
    VelocityComponent playerVelocity = VELOCITY_ZERO;
    SDL_Texture* playerTexture = loadTexture("Assets/Default/DefaultObject.png", g_renderer);
    AnimationComponent playerAnimation = ANIMATION_ZERO;

    // Ajouter des composants à l'entité
    addInputComponent(playerEntity, playerInput);  
    addPositionComponent(playerEntity, playerPosition);
    addVelocityComponent(playerEntity, playerVelocity);
    addSpriteComponent(playerEntity, playerTexture, (SDL_Rect){0, 0, 64, 64});
    addAnimationComponent(playerEntity, playerAnimation);

    // Configurer les bindings
    bindEvent(playerEntity, SDLK_z, EVENT_TYPE_MOVE, "Up");
    bindEvent(playerEntity, SDLK_s, EVENT_TYPE_MOVE, "Down");
    bindEvent(playerEntity, SDLK_q, EVENT_TYPE_MOVE, "Left");
    bindEvent(playerEntity, SDLK_d, EVENT_TYPE_MOVE, "Right");
    bindEvent(playerEntity, SDL_BUTTON_LEFT, EVENT_TYPE_SHOOT, "Shoot");

    

    changeState(STATE_PLAYING);
    while (currentState != STATE_EXIT) {
        // Code supplémentaire si nécessaire
        handleState();
    }
    return 0;
}