#include "core.h"

#define NUM_ENEMIES 50

bool can_shoot = true;

void onClick(Event event) {
    if(!can_shoot) {
        return;
    } else {
        addTimerComponent(playerEntity, "reloading", 1.0f);
        can_shoot = false;
    }
        
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
    HitboxComponent bulletHitbox = {0, 0, bulletSize.width, bulletSize.height, true};
    
    // Calculer la direction du tir
    float directionX = mouseX - playerPosition->x;
    float directionY = mouseY - playerPosition->y;
    float length = sqrtf(directionX * directionX + directionY * directionY);
    
    // Normaliser la direction
    if (length != 0) {
        directionX /= length;
        directionY /= length;
    }
    
    float bulletSpeed = 1000.0f;
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
    float velX = 0.0f, velY = 0.0f, speed = 500;
    if (strcmp((char*)event.data, "Right") == 0) {
        velX = speed;
    } else if (strcmp((char*)event.data, "Left") == 0) {
        velX = -speed;
    } else if (strcmp((char*)event.data, "Up") == 0) {
        velY = -speed;
    } else if (strcmp((char*)event.data, "Down") == 0) {
        velY = speed;
    }
    velocity->velocityX = velX;
    velocity->velocityY = velY;
}

void onBullet_CollideWith_Enemy(Event event) {
    if (event.data == NULL) {
        printf("Error: event.data is NULL\n");
        return;
    }

    CollisionData* collisionData = (CollisionData*)event.data;

    if (collisionData == NULL) {
        return;
    }

    // Récupérer les entités impliquées dans la collision
    Entity entity1 = collisionData->entity1;
    Entity entity2 = collisionData->entity2;

    if (!isEntityEnabled(entity1) || !isEntityEnabled(entity2))  return;
    if (!hasTag(entity1, "Enemy") && !hasTag(entity2, "Bullet")) return;

    Entity enemy = entity1;
    Entity bullet = entity2;
    
    // Gestion de la collision pour l'ennemi
    if (hasDataValue(enemy, DATA_HEALTH)) {
        int health = getDataValue(enemy, DATA_HEALTH) - 20;
        setDataValue(enemy, DATA_HEALTH, health);

        if (health <= 0) {
            Entity enemyEntity = enemy;
            Event eventDeath = {EVENT_TYPE_DEATH, &enemyEntity};
            emitEvent(eventDeath);
        }
    }
    disableEntity(bullet);
}

void onEnemy_CollideWith_Player(Event event) {
    if (event.data == NULL) {
        return;
    }

    CollisionData* collisionData = (CollisionData*)event.data;

    if (collisionData == NULL) {
        return;
    }

    // Récupérer les entités impliquées dans la collision
    Entity entity1 = collisionData->entity1;
    Entity entity2 = collisionData->entity2;

    if ( !isEntityEnabled(entity1) || !isEntityEnabled(entity2)) {
       return;
    }

    Entity player = INVALID_ENTITY_ID;
    Entity enemy = INVALID_ENTITY_ID;

    if (hasTag(entity1, "Enemy") && hasTag(entity2, "Player")) {
        enemy = entity1;
        player = entity2;
    } else {
        return;
    }

    // Gestion de la collision pour l'ennemi
    if (hasDataValue(player, DATA_HEALTH)) {
        int health = getDataValue(player, DATA_HEALTH) - 20;
        setDataValue(player, DATA_HEALTH, health);
        getHitboxComponent(player)->is_active = false;
        addTimerComponent(player, "immunity", 0.250f);

        if (health <= 0) {
            Entity* playerEntity = malloc(sizeof(Entity));
            *playerEntity = player;
            Event eventDeath = {EVENT_TYPE_DEATH, playerEntity};
            emitEvent(eventDeath);
        }
    }
    disableEntity(enemy);
}

void onDeath(Event event) {
    if (event.data == NULL) {
        printf("Error: event.data is NULL\n");
        return;
    }

    Entity entity = event.data;   
    if (hasTag(entity, "Enemy") || hasTag(entity, "Player")) {
        printf("Entity %u has died\n", entity);
        disableEntity(entity);
        if (entity == playerEntity) {
            changeState(STATE_GAME_OVER);
        }
    }
}

void uponReloading(Event event) {
     if (event.data == NULL) {
        return;
    }

    TimerData* timerData = (TimerData*)event.data;

    if (timerData == NULL) {
        return;
    }

    // Récupérer les entités impliquées dans la collision
    Entity player = timerData->entity;
    char* name = timerData->name;   

    if(strcmp(name, "reloading") == 0) {
        can_shoot = true;
    }

}

void uponInvincibilityFinished(Event event) {
    if (event.data == NULL) {
        printf("Error: event.data is NULL\n");
        return;
    }

    TimerData* timerData = (TimerData*)event.data;

    if (timerData == NULL) {
        printf("Error: Failed to cast event.data to TimerData*\n");
        return;
    }

    Entity player = timerData->entity;
    char* name = timerData->name;

    if (strcmp(name, "immunity") == 0) {
        getHitboxComponent(player)->is_active = true;
    }
}


int main(int argc, char* argv[]) {
    Init_All();

    // Ajouter des listeners pour les événements
    addEventListener(EVENT_TYPE_MOVE, onMove);
    addEventListener(EVENT_TYPE_LEFT_MOUSECLICK, onClick);
    addEventListener(EVENT_TYPE_COLLIDE, onBullet_CollideWith_Enemy);
    addEventListener(EVENT_TYPE_COLLIDE, onEnemy_CollideWith_Player);
    addEventListener(EVENT_TYPE_DEATH, onDeath);
    addEventListener(EVENT_TYPE_TIMER_EXPIRED, uponReloading);
    addEventListener(EVENT_TYPE_TIMER_EXPIRED, uponInvincibilityFinished);

    srand(time(NULL));  // Initialise le générateur de nombres aléatoires
    
    // Définition du fond d'écran
    Entity background = createEntity();
    PositionComponent backgroundPosition = POSITION_ZERO;
    SDL_Texture* backgroundTexture = loadColor(g_renderer, COLOR_WHITE, WINDOW_WIDTH, WINDOW_HEIGHT);
    addPositionComponent(background, backgroundPosition);
    addSpriteComponent(background, backgroundTexture, (SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT});

    // Créer plusieurs ennemis avec des positions aléatoires
    for (int i = 0; i < NUM_ENEMIES; ++i) {
        Entity enemy = createEntity();
        float speedMultiplier = 10.0f;

        // Générer une position aléatoire le long des bords de l'écran
        int edge = rand() % 4;  // 0 = haut, 1 = droite, 2 = bas, 3 = gauche
        int x, y;
        switch (edge) {
            case 0:  // Haut
                x = rand() % WINDOW_WIDTH;
                y = 0;
                break;
            case 1:  // Droite
                x = WINDOW_WIDTH - 32;
                y = rand() % WINDOW_HEIGHT;
                break;
            case 2:  // Bas
                x = rand() % WINDOW_WIDTH;
                y = WINDOW_HEIGHT - 32;
                break;
            case 3:  // Gauche
                x = 0;
                y = rand() % WINDOW_HEIGHT;
                break;
        }

        PositionComponent enemyPosition = {x, y};
        SizeComponent enemySize = {32, 32};
        HitboxComponent enemyHitbox = { 0, 0, enemySize.width, enemySize.height, true};
        DataComponent enemyData = DATA_COMPONENT_DEFAULT;
        SDL_Texture* enemyTexture = loadTexture("Assets/Default/DefaultObject.png", g_renderer);

        // Calcul de la direction vers le centre de l'écran
        int centerX = WINDOW_WIDTH / 2;
        int centerY = WINDOW_HEIGHT / 2;
        float deltaX = centerX - x;
        float deltaY = centerY - y;
        float magnitude = sqrt(deltaX * deltaX + deltaY * deltaY);
        VelocityComponent enemyVelocity = { 
            (deltaX / magnitude) * speedMultiplier, 
            (deltaY / magnitude) * speedMultiplier 
        };

        // Ajouter les composants à l'entité
        addPositionComponent(enemy, enemyPosition);
        addSizeComponent(enemy, enemySize);
        addHitboxComponent(enemy, enemyHitbox);
        addDataComponent(enemy, enemyData);
        addSpriteComponent(enemy, enemyTexture, (SDL_Rect){0, 0, enemySize.width, enemySize.height});
        addVelocityComponent(enemy, enemyVelocity);
        setDataValue(enemy, DATA_HEALTH, 100);
        addTag(enemy, "Enemy");
    }

    // Définition du player
    playerEntity = createEntity();
    InputComponent playerInput = INPUT_EMPTY;
    PositionComponent playerPosition = {WINDOW_WIDTH/2 - 16, WINDOW_HEIGHT/2};
    VelocityComponent playerVelocity = VELOCITY_ZERO;
    SizeComponent playerSize = {32, 32};
    HitboxComponent playerHitbox = { 0, 0, playerSize.width, playerSize.height, true};
    DataComponent playerData = DATA_COMPONENT_DEFAULT;
    SDL_Texture* playerTexture = loadTexture("Assets/Default/DefaultObject.png", g_renderer);
    addInputComponent(playerEntity, playerInput);  
    addPositionComponent(playerEntity, playerPosition);
    addVelocityComponent(playerEntity, playerVelocity);
    addSpriteComponent(playerEntity, playerTexture, (SDL_Rect){0, 0, 32, 32});
    addSizeComponent(playerEntity, playerSize);
    addHitboxComponent(playerEntity, playerHitbox);
    addDataComponent(playerEntity, playerData);
    addTag(playerEntity, "Player");
    setDataValue(playerEntity, DATA_HEALTH, 100);

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