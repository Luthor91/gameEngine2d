#include "timer.h"

void uponReloading(Event event) {
    if (!CheckTimerName(event, "reloading")) return;
    setDataValue(playerEntity, DATA_CAPABLE, 1.0f);    
}

void uponInvincibilityFinished(Event event) {
    if (!CheckTimerName(event, "immunity")) return;

    TimerData* timerData = (TimerData*)event.data;
    Entity player = timerData->entity;
    getHitboxComponent(player)->is_active = true;
}

void uponIncreasingDifficulty(Event event) {
    if (!CheckTimerName(event, "difficulty_increase")) return;
    if(getDataValue(playerEntity, DATA_DIFFICULTY) > 10.0f) return;
    setDataValue(
        playerEntity, 
        DATA_DIFFICULTY, 
        getDataValue(playerEntity, DATA_DIFFICULTY)+1.0f
    );
    printf("Difficulty increasing to %lf\n", getDataValue(playerEntity, DATA_DIFFICULTY));
}

void uponSpawningEnemies(Event event) {
    if (!CheckTimerName(event, "spawn_enemies")) return;
    printf("spawning enemies\n");

    for (int i = 0; i < ENEMIES_PER_SPAWN; ++i) {
        Entity enemy = (createEntity() != INVALID_ENTITY_ID) ? createEntity() : getFirstEmptyEntity();
        if (enemy == INVALID_ENTITY_ID) return;
        
        float speedMultiplier = 5.0f * (1 + (getDataValue(playerEntity, DATA_DIFFICULTY)/2.0f));
        int edge = rand() % 4, x = 0, y = 0;

        switch (edge) {
            case 0:  // Haut
                x = rand() % WINDOW_WIDTH - 32, y = 0;
                break;
            case 1:  // Droite
                x = WINDOW_WIDTH - 32, y = rand() % WINDOW_HEIGHT;
                break;
            case 2:  // Bas
                x = rand() % WINDOW_WIDTH - 32, y = WINDOW_HEIGHT - 32;
                break;
            case 3:  // Gauche
                x = 0, y = rand() % WINDOW_HEIGHT;
                break;
        }

        PositionComponent enemyPosition = {x, y};
        SizeComponent enemySize = {32, 32};
        HitboxComponent enemyHitbox = { 0, 0, enemySize.width, enemySize.height, true};
        DataComponent enemyData = DATA_COMPONENT_DEFAULT;
        SDL_Texture* enemyTexture = loadTexture("Assets/Default/DefaultEnemy.png", g_renderer);

        // Calcul de la direction vers le centre de l'écran
        float deltaX = (WINDOW_WIDTH / 2) - x;
        float deltaY = (WINDOW_HEIGHT / 2) - y;
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
        SpriteComponent enemySprite = {
            enemyTexture, 
            (SDL_Rect){0, 0, enemySize.width, enemySize.height}
        };
        addSpriteComponent(enemy, enemySprite);
        addVelocityComponent(enemy, enemyVelocity);
        setDataValue(enemy, DATA_HEALTH, 100*getDataValue(playerEntity, DATA_DIFFICULTY));
        setDataValue(enemy, DATA_ATTACK, 20*getDataValue(playerEntity, DATA_DIFFICULTY));
        addTag(enemy, "Enemy");
    }
}

void uponDispawningTrap(Event event) {  
    if (!CheckTimerName(event, "dispawn_trap")) return;
    printf("dispawn traps\n");

    TimerData* timerData = (TimerData*)event.data;
    Entity trap = timerData->entity;
    disableEntity(trap);
}


void uponSpawnBarrel(Event event) {
    if (!CheckTimerName(event, "spawn_barrel")) return;
    printf("spawn barrel\n");
    
    // Créer et configurer une nouvelle entité
    Entity barrel = createEntity();
    if (barrel == INVALID_ENTITY_ID) {
        printf("Failed to create barrel entity\n");
        return;
    }

    // Configurer les composants pour l'entité barrel
    VelocityComponent velocity = {0.0f, 0.0f};
    SizeComponent size = {64, 64};
    PositionComponent position = {
        .x = 0 + rand() % (WINDOW_WIDTH - (int)size.width),
        .y = 0 + rand() % (WINDOW_HEIGHT - (int)size.height)
    };
    HitboxComponent hitbox = {0.0f, 0.0f, size.width, size.height, true};
    DataComponent datas = DATA_COMPONENT_DEFAULT;

    // Créer une texture rouge avec un peu de transparence
    SDL_Texture* barrelTexture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (int)size.width, (int)size.height);
    SDL_SetTextureBlendMode(barrelTexture, SDL_BLENDMODE_BLEND); // Activer le blending pour la transparence
    SDL_SetRenderTarget(g_renderer, barrelTexture);
    SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 64); // Rouge avec transparence
    SDL_RenderClear(g_renderer);
    SDL_SetRenderTarget(g_renderer, NULL);

    // Créer le SpriteComponent pour le barrel
    SpriteComponent barrelSprite = {
        .texture = barrelTexture,
        .srcRect = {0, 0, (int)size.width, (int)size.height}
    };

    // Ajouter les composants à l'entité
    addPositionComponent(barrel, position);
    addVelocityComponent(barrel, velocity);
    addSizeComponent(barrel, size);
    addHitboxComponent(barrel, hitbox);
    addSpriteComponent(barrel, barrelSprite);
    setDataValue(barrel, DATA_ATTACK, getDataValue(playerEntity, DATA_ATTACK) * 0.1);
    setDataValue(barrel, DATA_SCORE, 0.0f);
    addTag(barrel, "Barrel");
    addTimerComponent(barrel, "dispawn_barrel", 5.0f, false);
}

void uponDispawnBarrel(Event event) {  
    if (!CheckTimerName(event, "dispawn_barrel")) return;
    printf("dispawn barrel\n");

    TimerData* timerData = (TimerData*)event.data;
    Entity barrel = timerData->entity;
    disableEntity(barrel);
}