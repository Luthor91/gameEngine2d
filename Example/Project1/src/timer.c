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

