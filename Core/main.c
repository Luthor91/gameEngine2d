#include "core.h"

#define NUM_ENEMIES 50

bool can_shoot = true;

void onBullet_Shoot(Event event) {
    if(!can_shoot) {
        return;
    } else {
        addTimerComponent(player_entity, "reloading", 1.0f);
        can_shoot = false;
    }
        
    Entity bullet = createEntity();

    PositionComponent* player_position = getPositionComponent(player_entity);
    SpriteComponent* player_sprite = getSpriteComponent(player_entity);

    // Calculer le centre du sprite du joueur
    float player_center_x = player_position->x + player_sprite->srcRect.w / 2;
    float player_center_y = player_position->y + player_sprite->srcRect.h / 2;
    
    // Récupérer la position du curseur de la souris
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    
    PositionComponent bullet_position = {player_center_x, player_center_y};
    VelocityComponent bulletVelocity = VELOCITY_ZERO;
    SizeComponent bullet_size = {12, 12};
    HitboxComponent bullet_hitbox = {0, 0, bullet_size.width, bullet_size.height, true};
    
    // Calculer la direction du tir
    float direction_x = mouse_x - player_position->x;
    float direction_y = mouse_y - player_position->y;
    float length = sqrtf(direction_x * direction_x + direction_y * direction_y);
    
    // Normaliser la direction
    if (length != 0) {
        direction_x /= length;
        direction_y /= length;
    }
    
    float bulletSpeed = 1000.0f;
    bulletVelocity.velocityX = direction_x * bulletSpeed;
    bulletVelocity.velocityY = direction_y * bulletSpeed;
    SDL_Texture* bulletTexture = loadColor(g_renderer, COLOR_BLACK, bullet_size.width, bullet_size.height);

    addPositionComponent(bullet, bullet_position);
    addSizeComponent(bullet, bullet_size);
    addVelocityComponent(bullet, bulletVelocity);
    addSpriteComponent(bullet, bulletTexture, (SDL_Rect){0, 0, bullet_size.width, bullet_size.height});
    addHitboxComponent(bullet, bullet_hitbox);
    addTag(bullet, "Bullet");
}

void onMove(Event event) {
    Entity player = player_entity;
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

    CollisionData* collision_data = (CollisionData*)event.data;

    if (collision_data == NULL) {
        return;
    }

    // Récupérer les entités impliquées dans la collision
    Entity entity1 = collision_data->entity1;
    Entity entity2 = collision_data->entity2;

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
            Event event_death = {EVENT_DEATH, &enemyEntity};
            emitEvent(event_death);
        }
    }
    disableComponentEntity(bullet);
}

void onEnemy_CollideWith_Player(Event event) {
    if (event.data == NULL) {
        return;
    }

    CollisionData* collision_data = (CollisionData*)event.data;

    if (collision_data == NULL) {
        return;
    }

    // Récupérer les entités impliquées dans la collision
    Entity entity1 = collision_data->entity1;
    Entity entity2 = collision_data->entity2;

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
            Entity* player_entity = malloc(sizeof(Entity));
            *player_entity = player;
            Event event_death = {EVENT_DEATH, player_entity};
            emitEvent(event_death);
        }
    }
    disableComponentEntity(enemy);
}

void onDeath(Event event) {
    if (event.data == NULL) {
        printf("Error: event.data is NULL\n");
        return;
    }

    Entity entity = event.data;   
    if (hasTag(entity, "Enemy") || hasTag(entity, "Player")) {
        printf("Entity %u has died\n", entity);
        disableComponentEntity(entity);
        if (entity == player_entity) {
            changeState(STATE_GAME_OVER);
        }
    }
}

void uponReloading(Event event) {
     if (event.data == NULL) {
        return;
    }

    TimerData* timer_data = (TimerData*)event.data;

    if (timer_data == NULL) {
        return;
    }

    // Récupérer les entités impliquées dans la collision
    Entity player = timer_data->entity;
    char* name = timer_data->name;   

    if(strcmp(name, "reloading") == 0) {
        can_shoot = true;
    }

}

void uponInvincibilityFinished(Event event) {
    if (event.data == NULL) {
        printf("Error: event.data is NULL\n");
        return;
    }

    TimerData* timer_data = (TimerData*)event.data;

    if (timer_data == NULL) {
        printf("Error: Failed to cast event.data to TimerData*\n");
        return;
    }

    Entity player = timer_data->entity;
    char* name = timer_data->name;

    if (strcmp(name, "immunity") == 0) {
        getHitboxComponent(player)->is_active = true;
    }
}


int main(int argc, char* argv[]) {
    Init_All();

    // Ajouter des listeners pour les événements
    addEventListener(EVENT_MOVE, onMove);
    addEventListener(EVENT_LEFT_MOUSECLICK, onBullet_Shoot);
    addEventListener(EVENT_COLLIDE, onBullet_CollideWith_Enemy);
    addEventListener(EVENT_COLLIDE, onEnemy_CollideWith_Player);
    addEventListener(EVENT_DEATH, onDeath);
    addEventListener(EVENT_TIMER_EXPIRED, uponReloading);
    addEventListener(EVENT_TIMER_EXPIRED, uponInvincibilityFinished);

    srand(time(NULL));  // Initialise le générateur de nombres aléatoires
    
    // Définition du fond d'écran
    Entity background = createEntity();
    PositionComponent background_position = POSITION_ZERO;
    SDL_Texture* backgroundTexture = loadColor(g_renderer, COLOR_WHITE, WINDOW_WIDTH, WINDOW_HEIGHT);
    addPositionComponent(background, background_position);
    addSpriteComponent(background, backgroundTexture, (SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT});

    // Créer plusieurs ennemis avec des positions aléatoires
    for (int i = 0; i < NUM_ENEMIES; ++i) {
        Entity enemy = createEntity();
        float speed_multiplier = 10.0f;

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

        PositionComponent enemy_position = {x, y};
        SizeComponent enemy_size = {32, 32};
        HitboxComponent enemy_hitbox = { 0, 0, enemy_size.width, enemy_size.height, true};
        DataComponent enemy_data = DATA_COMPONENT_DEFAULT;
        SDL_Texture* enemy_texture = loadTexture("Assets/Default/DefaultObject.png", g_renderer);

        // Calcul de la direction vers le centre de l'écran
        int centerX = WINDOW_WIDTH / 2;
        int centerY = WINDOW_HEIGHT / 2;
        float delta_x = centerX - x;
        float delta_y = centerY - y;
        float magnitude = sqrt(delta_x * delta_x + delta_y * delta_y);
        VelocityComponent enemy_velocity = { 
            (delta_x / magnitude) * speed_multiplier, 
            (delta_y / magnitude) * speed_multiplier 
        };

        // Ajouter les composants à l'entité
        addPositionComponent(enemy, enemy_position);
        addSizeComponent(enemy, enemy_size);
        addHitboxComponent(enemy, enemy_hitbox);
        addDataComponent(enemy, enemy_data);
        addSpriteComponent(enemy, enemy_texture, (SDL_Rect){0, 0, enemy_size.width, enemy_size.height});
        addVelocityComponent(enemy, enemy_velocity);
        setDataValue(enemy, DATA_HEALTH, 100);
        addTag(enemy, "Enemy");
    }

    // Définition du player
    player_entity = createEntity();
    InputComponent playerInput = INPUT_EMPTY;
    PositionComponent player_position = {WINDOW_WIDTH/2 - 16, WINDOW_HEIGHT/2};
    VelocityComponent playerVelocity = VELOCITY_ZERO;
    SizeComponent player_size = {32, 32};
    HitboxComponent player_hitbox = { 0, 0, player_size.width, player_size.height, true};
    DataComponent player_data = DATA_COMPONENT_DEFAULT;
    SDL_Texture* player_texture = loadTexture("Assets/Default/DefaultObject.png", g_renderer);
    addInputComponent(player_entity, playerInput);  
    addPositionComponent(player_entity, player_position);
    addVelocityComponent(player_entity, playerVelocity);
    addSpriteComponent(player_entity, player_texture, (SDL_Rect){0, 0, 32, 32});
    addSizeComponent(player_entity, player_size);
    addHitboxComponent(player_entity, player_hitbox);
    addDataComponent(player_entity, player_data);
    addTag(player_entity, "Player");
    setDataValue(player_entity, DATA_HEALTH, 100);

    // Configurer les bindings
    bindEvent(player_entity, SDLK_z, EVENT_MOVE, "Up");
    bindEvent(player_entity, SDLK_s, EVENT_MOVE, "Down");
    bindEvent(player_entity, SDLK_q, EVENT_MOVE, "Left");
    bindEvent(player_entity, SDLK_d, EVENT_MOVE, "Right");
    bindEvent(player_entity, SDL_BUTTON_LEFT, EVENT_LEFT_MOUSECLICK, "Shoot");

    changeState(STATE_PLAYING);
    while (current_state != STATE_EXIT) {
        handleState();
    }

    return 0;
}