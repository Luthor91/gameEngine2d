#include "timer.h"

void uponReloading(Event event) {
    if (!CheckTimerName(event, "reloading")) return;
    setDataValue(
        player_entity, 
        getDataType("DATA_CAN_SHOOT"), 
        1.0f
    );    
}

void uponInvincibilityFinished(Event event) {
    if (!CheckTimerName(event, "immunity")) return;

    TimerData* timer_data = (TimerData*)event.data;
    Entity player = timer_data->entity;
    getHitboxComponent(player)->is_active = true;
}

void uponIncreasingDifficulty(Event event) {
    if (!CheckTimerName(event, "difficulty_increase")) return;
    int DATA_DIFFICULTY = getDataType("DATA_DIFFICULTY");
    if(getDataValue(player_entity, DATA_DIFFICULTY) >= 10.0f) return;
    setDataValue(
        player_entity, 
        DATA_DIFFICULTY, 
        getDataValue(player_entity, DATA_DIFFICULTY)+1.0f
    );
    printf("Difficulty increasing to %lf\n", getDataValue(player_entity, DATA_DIFFICULTY));
}

void uponSpawnEnemies(Event event) {
    if (!CheckTimerName(event, "spawn_enemies")) return;
    printf("spawning enemies\n");
    int DATA_DIFFICULTY = getDataType("DATA_DIFFICULTY");
    int DATA_HEALTH = getDataType("DATA_HEALTH");
    int DATA_MAX_HEALTH = getDataType("DATA_MAX_HEALTH");
    int DATA_ATTACK = getDataType("DATA_ATTACK");

    for (int i = 0; i < ENEMIES_PER_SPAWN; ++i) {
        Entity enemy = (createEntity() != INVALID_ENTITY_ID) ? createEntity() : getFirstEmptyEntity();
        if (enemy == INVALID_ENTITY_ID) return;
        
        float speed_multiplier = 5.0f * (getDataValue(player_entity, DATA_DIFFICULTY) + 1);
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

        PositionComponent enemy_position = {x, y};
        SizeComponent enemy_size = {32, 32};
        HitboxComponent enemy_hitbox = { 0, 0, enemy_size.width, enemy_size.height, true};
        DataComponent enemy_data = DATA_COMPONENT_DEFAULT;
        SDL_Texture* enemy_texture = loadTexture("Assets/TowerDefense/EnemyFullHealth.png", g_renderer);

        // Calcul de la direction vers le centre de l'écran
        float delta_x = (WINDOW_WIDTH / 2) - x;
        float delta_y = (WINDOW_HEIGHT / 2) - y;
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
        SpriteComponent enemy_sprite = {
            enemy_texture, 
            (SDL_Rect){0, 0, enemy_size.width, enemy_size.height}
        };
        addSpriteComponent(enemy, enemy_sprite);
        addVelocityComponent(enemy, enemy_velocity);
        setDataValue(enemy, DATA_HEALTH, 100*getDataValue(player_entity, DATA_DIFFICULTY));
        setDataValue(enemy, DATA_MAX_HEALTH, getDataValue(player_entity, DATA_HEALTH));
        setDataValue(enemy, DATA_ATTACK, 20*getDataValue(player_entity, DATA_DIFFICULTY));
        addTag(enemy, "Enemy");
    }
}

void uponDispawnTrap(Event event) {  
    if (!CheckTimerName(event, "dispawn_trap")) return;
    printf("dispawn traps\n");

    TimerData* timer_data = (TimerData*)event.data;
    Entity trap = timer_data->entity;
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

    TimerData* timer_data = (TimerData*)event.data;
    Entity barrel = timer_data->entity;
    disableComponentEntity(barrel);
}

void uponSpawnPoison(Event event) {
    if (!CheckTimerName(event, "spawn_poison")) return;
    printf("spawn poison\n");
    summonPoison();
}

void uponApplyingPoisonTicks(Event event) {
    if (!CheckTimerName(event, "apply_poison_tick")) return;

    TimerData* timer_data = (TimerData*)event.data;
    Entity poison = timer_data->entity;
    HitboxComponent hitbox = *getHitboxComponent(poison);
    PositionComponent* poison_pos = getPositionComponent(poison);
    SizeComponent* poison_size = getSizeComponent(poison);

    int DATA_HEALTH = getDataType("DATA_HEALTH");
    int DATA_ATTACK = getDataType("DATA_ATTACK");

    if (poison_pos == NULL || poison_size == NULL) {
        printf("Poison is missing Position or Size component\n");
        return;
    }

    SDL_Rect poison_area = {
        .x = poison_pos->x,
        .y = poison_pos->y,
        .w = poison_size->width,
        .h = poison_size->height
    };

    float damage = getDataValue(poison, DATA_ATTACK);
    int count = 0;
    Entity* enemies = getEntitiesWithTag("Enemy", &count);

    for (int index = 0; index < count; index++) {
        Entity enemy = enemies[index];
        PositionComponent* enemy_pos = getPositionComponent(enemy);
        SizeComponent* enemy_size = getSizeComponent(enemy);

        SDL_Rect enemy_area = {
            .x = enemy_pos->x,
            .y = enemy_pos->y,
            .w = enemy_size->width,
            .h = enemy_size->height
        };

        if (SDL_HasIntersection(&poison_area, &enemy_area)) {
            float health = getDataValue(enemy, DATA_HEALTH) - damage;
            setDataValue(enemy, DATA_HEALTH, health);

            PositionComponent pos_centered = *getCenterPosition(enemy);
            setEmitterPosition("Poison", pos_centered.x, pos_centered.y);
            instanciateParticleEmitter("Poison");
            handle_damage_received(enemy, health);
            printf("Enemy %d hit by poison for %.2f damage\n", enemy, damage);
        }
    }

    hitbox.is_active = !hitbox.is_active;
    setDataValue(poison, DATA_ATTACK, getDataValue(poison, DATA_ATTACK) * 0.95);

    if (getDataValue(poison, DATA_ATTACK) < getDataValue(player_entity, DATA_ATTACK) * 0.05) {
        removeTimerComponent(poison, "apply_poison_tick"); 
        disableComponentEntity(poison);
    }

    printf("damage : %f\n", getDataValue(poison, DATA_ATTACK));
}


void uponDispawnBait(Event event) {  
    if (!CheckTimerName(event, "dispawn_bait")) return;
    printf("dispawn bait\n");

    TimerData* timer_data = (TimerData*)event.data;
    Entity bait = timer_data->entity;
    PositionComponent position_player = *getPositionComponent(player_entity);
    // Faire changer la direction des ennemis vers le joueur
    int count = 0;
    Entity* enemies = getEntitiesWithTag("Enemy", &count);
    for (int index = 0; index < count; index++) {
        Entity enemy = enemies[index];
        adjustEnemyDirection(enemy, position_player);
    }

    disableComponentEntity(bait);
}
