#include "core.h"

void onClick(Event event) {
    Entity bullet = createEntity();
    
    PositionComponent* playerPosition = getPositionComponent(playerEntity);
    SpriteComponent* playerSprite = getSpriteComponent(playerEntity);

    // Calculer le centre du sprite du joueur
    float playerCenterX = playerPosition->x + playerSprite->srcRect.w / 2;
    float playerCenterY = playerPosition->y + playerSprite->srcRect.h / 2;
    
    // Récupérer la position du curseur de la souris
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    
    PositionComponent bulletPosition = {playerCenterX, playerCenterY};
    VelocityComponent bulletVelocity = VELOCITY_ZERO;
    SizeComponent bulletSize = {12, 12};
    HitboxComponent bulletHitbox = {0, 0, bulletSize.width, bulletSize.height};
    
    // Calculer la direction du tir
    float directionX = mouseX - playerPosition->x;
    float directionY = mouseY - playerPosition->y;
    float length = sqrtf(directionX * directionX + directionY * directionY);
    
    // Normaliser la direction
    if (length != 0) {
        directionX /= length;
        directionY /= length;
    }
    
    float bulletSpeed = 500.0f;
    bulletVelocity.velocityX = directionX * bulletSpeed;
    bulletVelocity.velocityY = directionY * bulletSpeed;
    SDL_Texture* bulletTexture = loadColor(g_renderer, COLOR_BLACK, bulletSize.width, bulletSize.height);

    addPositionComponent(bullet, bulletPosition);
    addSizeComponent(bullet, bulletSize);
    addVelocityComponent(bullet, bulletVelocity);
    addSpriteComponent(bullet, bulletTexture, (SDL_Rect){0, 0, bulletSize.width, bulletSize.height});
    addHitboxComponent(bullet, bulletHitbox);
    addTag(bullet, "Bullet");
}

void onMove(Event event) {
    Entity player = playerEntity;
    if (!hasVelocity[player] || player == INVALID_ENTITY_ID) return;
    
    VelocityComponent* velocity = getVelocityComponent(player);
    float velX = 0.0f, velY = 0.0f;
    if (strcmp((char*)event.data, "Right") == 0) {
        velX = 100;
    } else if (strcmp((char*)event.data, "Left") == 0) {
        velX = -100;
    } else if (strcmp((char*)event.data, "Up") == 0) {
        velY = -100;
    } else if (strcmp((char*)event.data, "Down") == 0) {
        velY = 100;
    }
    velocity->velocityX = velX;
    velocity->velocityY = velY;
}

void onCollision(Event event) {
    if (event.data == NULL) {
        printf("Error: event.data is NULL\n");
        return;
    }

    CollisionData* collisionData = (CollisionData*)event.data;

    if (collisionData == NULL) {
        printf("Error: Failed to cast event.data to CollisionData*\n");
        return;
    }

    // Récupérer les entités
    Entity entity1 = collisionData->entity1;
    Entity entity2 = collisionData->entity2;

    // Afficher les entités impliquées dans la collision
    printf("Colliding between %u and %u\n", entity1, entity2);
    
    if (hasTagComponent(entity1) && hasTag(entity1, "Bullet")) {
        printf("Entity %u is valid, will be disabled\n", entity1);
        disableEntity(entity1);
    }
    if (hasTagComponent(entity2) && hasTag(entity2, "Bullet")) {
        printf("Entity %u is valid, will be disabled\n", entity2);
        disableEntity(entity2);
    }
    free(collisionData);
}

int main(int argc, char* argv[]) {

    Init_All();

    // Ajouter des listeners pour les événements
    addEventListener(EVENT_TYPE_MOVE, onMove);
    addEventListener(EVENT_TYPE_LEFT_MOUSECLICK, onClick);
    addEventListener(EVENT_TYPE_COLLIDE, onCollision);
    
    // Définition du fond d'écran
    Entity background = createEntity();
    PositionComponent backgroundPosition = POSITION_ZERO;  
    SDL_Texture* backgroundTexture = loadColor(g_renderer, COLOR_WHITE, WINDOW_WIDTH, WINDOW_HEIGHT);
    addPositionComponent(background, backgroundPosition);
    addSpriteComponent(background, backgroundTexture, (SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT});

    // Définition d'un ennemie
    Entity enemy = createEntity();
    PositionComponent enemyPosition = {WINDOW_WIDTH - 64, 0};
    SizeComponent enemySize = {64, 64};
    HitboxComponent enemyHitbox = { 0, 0, enemySize.width, enemySize.height};
    SDL_Texture* enemyTexture = loadTexture("Assets/Default/DefaultObject.png", g_renderer);
    addPositionComponent(enemy, enemyPosition);
    addSizeComponent(enemy, enemySize);
    addHitboxComponent(enemy, enemyHitbox);
    addSpriteComponent(enemy, enemyTexture, (SDL_Rect){0, 0, enemySize.width, enemySize.height});

    // Définition du player
    playerEntity = createEntity();
    InputComponent playerInput = INPUT_EMPTY;
    PositionComponent playerPosition = {0, WINDOW_HEIGHT - 64};
    VelocityComponent playerVelocity = VELOCITY_ZERO;
    SDL_Texture* playerTexture = loadTexture("Assets/Default/DefaultObject.png", g_renderer);
    addInputComponent(playerEntity, playerInput);  
    addPositionComponent(playerEntity, playerPosition);
    addVelocityComponent(playerEntity, playerVelocity);
    addSpriteComponent(playerEntity, playerTexture, (SDL_Rect){0, 0, 64, 64});

    // Configurer les bindings
    bindEvent(playerEntity, SDLK_z, EVENT_TYPE_MOVE, "Up");
    bindEvent(playerEntity, SDLK_s, EVENT_TYPE_MOVE, "Down");
    bindEvent(playerEntity, SDLK_q, EVENT_TYPE_MOVE, "Left");
    bindEvent(playerEntity, SDLK_d, EVENT_TYPE_MOVE, "Right");
    bindEvent(playerEntity, SDL_BUTTON_LEFT, EVENT_TYPE_LEFT_MOUSECLICK, "Shoot");

    changeState(STATE_PLAYING);
    while (currentState != STATE_EXIT) {
        handleState();
    }
    
    return 0;
}