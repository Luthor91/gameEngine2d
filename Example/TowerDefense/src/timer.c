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

    if (!hasDataValue(player_entity, DATA_DIFFICULTY)) return;

    float difficulty = getDataValue(player_entity, DATA_DIFFICULTY);

    if(difficulty >= 10.0f) return;

    setDataValue(player_entity, DATA_DIFFICULTY, difficulty+1.0f);
    printf("Difficulty increasing to %lf\n", getDataValue(player_entity, DATA_DIFFICULTY));
}

void uponSpawnEnemies(Event event) {
    if (!CheckTimerName(event, "spawn_enemies")) return;
    
    int DATA_DIFFICULTY = getDataType("DATA_DIFFICULTY");
    int DATA_HEALTH = getDataType("DATA_HEALTH");
    int DATA_MAX_HEALTH = getDataType("DATA_MAX_HEALTH");
    int DATA_ATTACK = getDataType("DATA_ATTACK");

    if (!hasDataValue(player_entity, DATA_DIFFICULTY)) return;
    float difficulty = getDataValue(player_entity, DATA_DIFFICULTY);

    int count = 0;
    getEntitiesWithTag("Enemy", &count);

    for (int i = 0; i < ENEMIES_PER_SPAWN; ++i) {
        if (count + i >= MAX_ENEMIES_SCREEN) return;
        Entity enemy = createEntity();
        if (enemy == INVALID_ENTITY_ID) continue;
        
        float speed_multiplier = 5.0f * (getDataValue(player_entity, DATA_DIFFICULTY) + 1);
        int edge = rand() % 4, x = 0, y = 0;

        switch (edge) {
            case 0:  // Haut
                x = rand() % game.window_width - 32, y = 0;
                break;
            case 1:  // Droite
                x = game.window_width - 32, y = rand() % game.window_height;
                break;
            case 2:  // Bas
                x = rand() % game.window_width - 32, y = game.window_height - 32;
                break;
            case 3:  // Gauche
                x = 0, y = rand() % game.window_height;
                break;
        }

        PositionComponent enemy_position = {x, y};
        SizeComponent enemy_size = {32, 32};
        HitboxComponent enemy_hitbox = { 0, 0, enemy_size.width, enemy_size.height, true};
        DataComponent enemy_data = DATA_COMPONENT_DEFAULT;
        SDL_Texture* enemy_texture = loadTexture("Assets/TowerDefense/EnemyFullHealth.png", game.renderer);

        // Calcul de la direction vers le centre de l'écran
        float delta_x = (game.window_width / 2) - x;
        float delta_y = (game.window_height / 2) - y;
        float magnitude = sqrt(delta_x * delta_x + delta_y * delta_y);
        VelocityComponent enemy_velocity = { 
            (delta_x / magnitude) * speed_multiplier, 
            (delta_y / magnitude) * speed_multiplier 
        };
        SpriteComponent enemy_sprite = {
            enemy_texture, 
            (SDL_Rect){0, 0, enemy_size.width, enemy_size.height}
        };
        // Ajouter les composants à l'entité
        addPositionComponent(enemy, enemy_position);
        addSizeComponent(enemy, enemy_size);
        addHitboxComponent(enemy, enemy_hitbox);
        addDataComponent(enemy, enemy_data);
        addSpriteComponent(enemy, enemy_sprite);
        addVelocityComponent(enemy, enemy_velocity);

        setDataValue(enemy, DATA_HEALTH, 100*difficulty);
        setDataValue(enemy, DATA_MAX_HEALTH, 100*difficulty);
        setDataValue(enemy, DATA_ATTACK, 20*difficulty);
        addTag(enemy, "Enemy");
    }
}

void uponDispawnTrap(Event event) {  
    if (!CheckTimerName(event, "dispawn_trap")) return;

    TimerData* timer_data = (TimerData*)event.data;
    Entity trap = timer_data->entity;
    disableComponentEntity(trap);
}

void uponSpawnBarrel(Event event) {
    if (!CheckTimerName(event, "spawn_barrel")) return;
    summonBarrel();
}

void uponDispawnBarrel(Event event) {  
    if (!CheckTimerName(event, "dispawn_barrel")) return;

    TimerData* timer_data = (TimerData*)event.data;
    Entity barrel = timer_data->entity;

    if (isEntityValid(barrel)) disableComponentEntity(barrel);
    return;
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

    if (!hasHitboxComponent(poison) || !hasPositionComponent(poison) || !hasSizeComponent(poison)) return;
    HitboxComponent hitbox = *getHitboxComponent(poison);
    PositionComponent poison_pos = *getPositionComponent(poison);
    SizeComponent poison_size = *getSizeComponent(poison);

    int DATA_MAX_PROC = getDataType("DATA_MAX_PROC");
    int DATA_HEALTH = getDataType("DATA_HEALTH");
    int DATA_ATTACK = getDataType("DATA_ATTACK");

    SDL_Rect poison_area = {
        .x = poison_pos.x,
        .y = poison_pos.y,
        .w = poison_size.width,
        .h = poison_size.height
    };

    if (!hasDataValue(poison, DATA_ATTACK) || !hasDataValue(poison, DATA_MAX_PROC)) return;
    float damage = getDataValue(poison, DATA_ATTACK);
    float max_poison_proc = getDataValue(poison, DATA_MAX_PROC);
    int current_poison_proc = 0;

    int count = 0;
    Entity* enemies = getEntitiesWithTag("Enemy", &count);
    for (int index = 0; index < count; index++) {
        if (current_poison_proc > max_poison_proc) break;
        
        Entity enemy = enemies[index];

        if (!hasPositionComponent(enemy) || !hasSizeComponent(enemy) || !hasDataValue(enemy, DATA_HEALTH)) continue;
        PositionComponent enemy_pos = *getPositionComponent(enemy);
        SizeComponent enemy_size = *getSizeComponent(enemy);

        SDL_Rect enemy_area = {
            .x = enemy_pos.x,
            .y = enemy_pos.y,
            .w = enemy_size.width,
            .h = enemy_size.height
        };

        if (SDL_HasIntersection(&poison_area, &enemy_area) ) {
            float health = getDataValue(enemy, DATA_HEALTH) - damage;
            setDataValue(enemy, DATA_HEALTH, health);
            setDataValue(
                player_entity, DATA_HEALTH, 
                getDataValue(player_entity, DATA_HEALTH) + (damage / 100)
            );

            PositionComponent pos_centered = *getCenterPosition(enemy);
            setEmitterPosition("Poison", pos_centered.x, pos_centered.y);
            instanciateParticleEmitter("Poison");

            handle_damage_received(enemy, health);
            current_poison_proc++;
        }
    }

    hitbox.is_active = !hitbox.is_active;
    setDataValue(poison, DATA_ATTACK, getDataValue(poison, DATA_ATTACK) * 0.95);
    if (getDataValue(poison, DATA_ATTACK) < getDataValue(player_entity, DATA_ATTACK) / 20.0f) {
        disableComponentEntity(poison);
    }
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
