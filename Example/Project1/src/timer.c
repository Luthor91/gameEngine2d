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

void uponSpawnEnemies(Event event) {
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

void uponDispawnTrap(Event event) {  
    if (!CheckTimerName(event, "dispawn_trap")) return;
    printf("dispawn traps\n");

    TimerData* timerData = (TimerData*)event.data;
    Entity trap = timerData->entity;
    disableComponentEntity(trap);
}


void uponSpawnBarrel(Event event) {
    if (!CheckTimerName(event, "spawn_barrel")) return;
    printf("spawn barrel\n");
    summonBarrel();
}

void uponDispawnBarrel(Event event) {  
    if (!CheckTimerName(event, "dispawn_barrel")) return;
    printf("dispawn barrel\n");

    TimerData* timerData = (TimerData*)event.data;
    Entity barrel = timerData->entity;
    disableComponentEntity(barrel);
}

void uponSpawnPoison(Event event) {
    if (!CheckTimerName(event, "spawn_poison")) return;
    printf("spawn poison\n");
    summonPoison();
}

void uponApplyingPoisonTicks(Event event) {
    if (!CheckTimerName(event, "apply_poison_tick")) return;

    TimerData* timerData = (TimerData*)event.data;
    Entity poison = timerData->entity;
    HitboxComponent hitbox = *getHitboxComponent(poison);
    PositionComponent* poison_pos = getPositionComponent(poison);
    SizeComponent* poison_size = getSizeComponent(poison);

    if (poison_pos == NULL || poison_size == NULL) {
        printf("Poison is missing Position or Size component\n");
        return;
    }

    // Définir les limites de la zone d'explosion du baril
    SDL_Rect poison_area = {
        .x = poison_pos->x,
        .y = poison_pos->y,
        .w = poison_size->width,
        .h = poison_size->height
    };

    float damage = getDataValue(poison, DATA_ATTACK);
    int count = 0;
    Entity* enemies = getEntitiesWithTag("Enemy", &count);
    // Parcourir toutes les entités et vérifier les ennemis dans la zone
    for (int index = 0; index < count; index++) {
        Entity enemy = enemies[index];
        PositionComponent* enemy_pos = getPositionComponent(enemy);
        SizeComponent* enemy_size = getSizeComponent(enemy);

        // Définir les limites de l'ennemi
        SDL_Rect enemy_area = {
            .x = enemy_pos->x,
            .y = enemy_pos->y,
            .w = enemy_size->width,
            .h = enemy_size->height
        };
        // Vérifier si l'ennemi est dans la zone d'explosion
        if (SDL_HasIntersection(&poison_area, &enemy_area)) {
            // Infliger des dégâts à l'ennemi
            float health = getDataValue(enemy, DATA_HEALTH) - damage;
            setDataValue(enemy, DATA_HEALTH, health);
            if (health <= 0) {
                Entity* enemyPtr = malloc(sizeof(Entity));
                *enemyPtr = enemy;
                Event eventDeath = {EVENT_TYPE_DEATH, enemyPtr};
                emitEvent(eventDeath);
            }
            printf("Enemy %d hit by poison for %.2f damage\n", enemy, damage);
        }
    }
    hitbox.is_active = hitbox.is_active ? false : true;

    setDataValue(poison, DATA_ATTACK, getDataValue(poison, DATA_ATTACK)*0.95);

    if (getDataValue(poison, DATA_ATTACK) < getDataValue(playerEntity, DATA_ATTACK) * 0.05) {
        TimerData* timerData = (TimerData*)event.data;
        Entity poison = timerData->entity;
        removeTimerComponent(poison, "apply_poison_tick"); 
        disableComponentEntity(poison);
    }
    
    printf("damage : %f\n", getDataValue(poison, DATA_ATTACK));
}

void uponDispawnBait(Event event) {  
    if (!CheckTimerName(event, "dispawn_bait")) return;
    printf("dispawn bait\n");

    TimerData* timerData = (TimerData*)event.data;
    Entity bait = timerData->entity;
    PositionComponent position_player = *getPositionComponent(playerEntity);
    // Faire changer la direction des ennemis vers le joueur
    int count = 0;
    Entity* enemies = getEntitiesWithTag("Enemy", &count);
    for (int index = 0; index < count; index++) {
        Entity enemy = enemies[index];
        adjustEnemyDirection(enemy, position_player);
    }

    disableComponentEntity(bait);
}