#include "effect.h"

// Effet lvl 2
void amplify_bullet(Entity bullet) {
    int DATA_ATTACK = getDataType("DATA_ATTACK");
    int DATA_COUNT_SHOOT = getDataType("DATA_COUNT_SHOOT");

    setDataValue(player_entity, DATA_COUNT_SHOOT, 0.0f);

    SizeComponent bullet_size = *getSizeComponent(bullet);
    VelocityComponent bullet_velocity = *getVelocityComponent(bullet);

    bullet_size.height *= 1.5f;
    bullet_size.width *= 1.5f;
    bullet_velocity.velocityX *= 2.0f;
    bullet_velocity.velocityY *= 2.0f;

    SpriteComponent sprite = {
    loadColor(g_renderer, COLOR_RED, bullet_size.width, bullet_size.height),
        (SDL_Rect){0, 0, bullet_size.width, bullet_size.height}
    };
    addSpriteComponent(bullet, sprite);
    setDataValue(bullet, DATA_ATTACK, getDataValue(bullet, DATA_ATTACK)*2.0f);
}

// Effet lvl 3
void summonSecondBullet(Entity bullet, float direction_x, float direction_y) {
    int DATA_ATTACK = getDataType("DATA_ATTACK");
    float coeff_passive = getDataValue(player_entity, getDataType("DATA_PASSIVE"));
    

    Entity second_bullet = copyEntity(bullet);
    SizeComponent bullet_size = *getSizeComponent(bullet);
    VelocityComponent velocity_second_bullet = {direction_x * 0.40f, direction_y * 0.40f};
    SpriteComponent second_bullet_sprite = {
        loadColor(g_renderer, COLOR_GREEN, bullet_size.width, bullet_size.height),
        (SDL_Rect){0, 0, bullet_size.width/coeff_passive, bullet_size.height/coeff_passive}
    };

    addVelocityComponent(second_bullet, velocity_second_bullet);
    addSpriteComponent(second_bullet, second_bullet_sprite);
    setDataValue(second_bullet, DATA_ATTACK, getDataValue(player_entity, DATA_ATTACK));
}

// Effet lvl 4
void summonTrap(PositionComponent death_position) {
    // Créer et configurer une nouvelle entité
    Entity trap = createEntity();
    if (trap == INVALID_ENTITY_ID) {
        printf("Failed to create trap entity\n");
        return;
    }

    // Configurer les composants pour l'entité trap
    VelocityComponent velocity = {0.0f, 0.0f};
    SizeComponent size = {60.0f, 60.0f};
    HitboxComponent hitbox = {0.0f, 0.0f, size.width, size.height, true};
    DataComponent trap_data = DATA_COMPONENT_DEFAULT;
    SpriteComponent trap_sprite = {
        loadTexture("Assets/TowerDefense/Trap.png", g_renderer),
        (SDL_Rect){0, 0, size.width, size.height}
    };

    int DATA_LEVEL = getDataType("DATA_LEVEL");
    int DATA_ATTACK = getDataType("DATA_ATTACK");

    addPositionComponent(trap, death_position);
    addVelocityComponent(trap, velocity);
    addSizeComponent(trap, size);
    addHitboxComponent(trap, hitbox);
    addSpriteComponent(trap, trap_sprite);
    setDataValue(trap, DATA_ATTACK, getDataValue(player_entity, DATA_ATTACK) + 0.25 * getDataValue(player_entity, DATA_LEVEL));
    addTag(trap, "Trap");
    addTimerComponent(trap, "dispawn_trap", 2.5f, false);
}

// Effet lvl 5
void killChance() {
    int count = 0;
    Entity* enemies = getEntitiesWithTag("Enemy", &count);
    int index = rand() % count - 1;

    int DATA_LEVEL = getDataType("DATA_LEVEL");
    int DATA_HEALTH = getDataType("DATA_HEALTH");
    int DATA_ATTACK = getDataType("DATA_ATTACK");

    if (getDataValue(player_entity, DATA_LEVEL)/2 >= rand() % 99) {
        Entity bullet = createEntity();
        Entity target = enemies[index];
        PositionComponent pos_target = *getPositionComponent(target);
        SizeComponent size_target = *getSizeComponent(target);
        PositionComponent pos = { 
            pos_target.x + size_target.width/2, 
            pos_target.y + size_target.height/2
        };
        HitboxComponent hitbox = {0, 0, 1, 1, true};
        DataComponent data = DATA_COMPONENT_DEFAULT;

        addPositionComponent(bullet, pos);
        addHitboxComponent(bullet, hitbox);
        addDataComponent(bullet, data);
        addTag(bullet, "Bullet");
        setDataValue(bullet, DATA_ATTACK, getDataValue(target, DATA_HEALTH));
    }
}

// Effet lvl 6
void summonBarrel() {
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
    DataComponent barrel_data = DATA_COMPONENT_DEFAULT;

    // Créer le SpriteComponent pour le barrel
    SpriteComponent barrel_sprite = {
        .texture = loadColor(g_renderer, (SDL_Color){255, 0, 0, 64}, size.width, size.height),
        .srcRect = {0, 0, (int)size.width, (int)size.height}
    };

    int DATA_ATTACK = getDataType("DATA_ATTACK");
    int DATA_KILLED = getDataType("DATA_KILLED");

    // Ajouter les composants à l'entité
    addPositionComponent(barrel, position);
    addVelocityComponent(barrel, velocity);
    addSizeComponent(barrel, size);
    addHitboxComponent(barrel, hitbox);
    addSpriteComponent(barrel, barrel_sprite);
    addDataComponent(barrel, barrel_data);
    setDataValue(barrel, DATA_ATTACK, getDataValue(player_entity, DATA_ATTACK) * 0.1);
    setDataValue(barrel, DATA_KILLED, 0.0f);
    addTag(barrel, "Barrel");
    addTimerComponent(barrel, "dispawn_barrel", 5.0f, false);
}

void explodeBarrel(Entity barrel) {
    PositionComponent* barrelPos = getPositionComponent(barrel);
    SizeComponent* barrelSize = getSizeComponent(barrel);

    if (barrelPos == NULL || barrelSize == NULL) {
        printf("Barrel is missing Position or Size component\n");
        return;
    }

    SDL_Rect explosionZone = {
        .x = barrelPos->x,
        .y = barrelPos->y,
        .w = barrelSize->width,
        .h = barrelSize->height
    };

    int DATA_ACCUMULATION = getDataType("DATA_ACCUMULATION");
    int DATA_ATTACK = getDataType("DATA_ATTACK");
    int DATA_HEALTH = getDataType("DATA_HEALTH");

    float damage = (getDataValue(barrel, DATA_ATTACK) * 0.70) * (1 + getDataValue(barrel, DATA_ACCUMULATION));
    int count = 0;
    Entity* enemies = getEntitiesWithTag("Enemy", &count);

    for (int index = 0; index < count; index++) {
        Entity enemy = enemies[index];
        PositionComponent* enemyPos = getPositionComponent(enemy);
        SizeComponent* enemy_size = getSizeComponent(enemy);

        SDL_Rect enemyZone = {
            .x = enemyPos->x,
            .y = enemyPos->y,
            .w = enemy_size->width,
            .h = enemy_size->height
        };

        if (SDL_HasIntersection(&explosionZone, &enemyZone)) {
            float health = getDataValue(enemy, DATA_HEALTH) - damage;
            setDataValue(enemy, DATA_HEALTH, health);

            // Si la santé de l'ennemi tombe à 0 ou en dessous, émettre un événement de mort
            handle_damage_received(enemy, health);
            printf("Enemy %d hit by barrel explosion for %.2f damage\n", enemy, damage);
        }
    }

    destroyEntity(barrel);
}

// Effet lvl 7
void summonPoison() {
    int count = 0;
    Entity* poisons = getEntitiesWithTag("Poison", &count);
    if (count > 0) return;  
    
    // Créer et configurer une nouvelle entité
    Entity poison = createEntity();
    if (poison == INVALID_ENTITY_ID) {
        printf("Failed to create trap entity\n");
        return;
    }

    // Configurer les composants pour l'entité trap
    SizeComponent size_poison = {120.0f, 120.0f};
    SizeComponent size_player = *getSizeComponent(player_entity);
    PositionComponent position_player = *getPositionComponent(player_entity);

    PositionComponent poison_position = {
        (position_player.x + size_player.width / 2) - size_poison.width / 2,
        (position_player.y + size_player.height / 2) - size_poison.height / 2
    };
    HitboxComponent hitbox = {0.0f, 0.0f, size_poison.width, size_poison.height, true};
    DataComponent poison_data = DATA_COMPONENT_DEFAULT;
    SpriteComponent poison_sprite = {
        loadColor(g_renderer, (SDL_Color){0, 255, 0, 64}, size_poison.width, size_poison.height),
        (SDL_Rect){0, 0, size_poison.width, size_poison.height}
    };
    int DATA_ATTACK = getDataType("DATA_ATTACK");

    addPositionComponent(poison, poison_position);
    addSizeComponent(poison, size_poison);
    addHitboxComponent(poison, hitbox);
    addSpriteComponent(poison, poison_sprite);
    addDataComponent(poison, poison_data);
    setDataValue(poison, DATA_ATTACK, getDataValue(player_entity, DATA_ATTACK));
    addTag(poison, "Poison");
    addTimerComponent(poison, "apply_poison_tick", 0.250f, true);
}

// Effet lvl 8
void adjustEnemyDirection(Entity enemy, PositionComponent bait_position) {
    PositionComponent* enemy_position = getPositionComponent(enemy);
    VelocityComponent* enemy_velocity = getVelocityComponent(enemy);

    if (enemy_position == NULL || enemy_velocity == NULL) {
        return; // Si l'ennemi n'a pas de composant de position ou de vélocité, ignorer
    }

    // Calculer la direction vers le "bait"
    float direction_x = bait_position.x - enemy_position->x;
    float direction_y = bait_position.y - enemy_position->y;
    float magnitude = sqrtf(direction_x * direction_x + direction_y * direction_y);

    // Normaliser la direction
    if (magnitude != 0) {
        direction_x /= magnitude;
        direction_y /= magnitude;
    }

    // Définir une vitesse propre à chaque ennemi ou utiliser une valeur fixe
    float speed = sqrtf(enemy_velocity->velocityX * enemy_velocity->velocityX + enemy_velocity->velocityY * enemy_velocity->velocityY);

    // Ajuster la vélocité de l'ennemi pour qu'il se dirige vers le "bait"
    enemy_velocity->velocityX = direction_x * speed;
    enemy_velocity->velocityY = direction_y * speed;
}

// Utility
void handle_damage_received(Entity entity, float health) {
    Entity* ptr_entity = malloc(sizeof(Entity));
    *ptr_entity = entity;
    if (health <= 0) {
        Event event_death = {getEventType("EVENT_DEATH"), ptr_entity};
        emitEvent(event_death);
    } else {
        Event event_damaged = {getEventType("EVENT_INFO"), ptr_entity};
        emitEvent(event_damaged);
    }
}
