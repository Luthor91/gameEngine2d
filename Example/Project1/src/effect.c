#include "effect.h"

void summonSecondBullet(Entity bullet, float directionX, float directionY, float coeff_passive) {
    Entity second_bullet = copyEntity(bullet);
    SizeComponent bulletSize = *getSizeComponent(bullet);
    VelocityComponent velocity_second_bullet = {directionX * 500.0f, directionY * 500.0f};
    SpriteComponent second_bullet_sprite = {
        loadColor(g_renderer, COLOR_GREEN, bulletSize.width, bulletSize.height),
        (SDL_Rect){0, 0, bulletSize.width/coeff_passive, bulletSize.height/coeff_passive}
    };
    addVelocityComponent(second_bullet, velocity_second_bullet);
    addSpriteComponent(second_bullet, second_bullet_sprite);
}

void summonTrap(PositionComponent deathPosition) {
    // Créer et configurer une nouvelle entité
    Entity trap = createEntity();
    if (trap == INVALID_ENTITY_ID) {
        printf("Failed to create trap entity\n");
        return;
    }

    // Configurer les composants pour l'entité trap
    VelocityComponent velocity = {0.0f, 0.0f};
    SizeComponent size = {60.0f, 60.0f};
    PositionComponent position = {
        deathPosition.x - size.width / 2,
        deathPosition.y - size.height / 2
    };
    HitboxComponent hitbox = {0.0f, 0.0f, size.width, size.height, true};
    DataComponent datas = DATA_COMPONENT_DEFAULT;
    SpriteComponent trapSprite = {
        loadTexture("Assets/Default/DefaultTrap.png", g_renderer),
        (SDL_Rect){0, 0, size.width, size.height}
    };

    addPositionComponent(trap, position);
    addVelocityComponent(trap, velocity);
    addSizeComponent(trap, size);
    addHitboxComponent(trap, hitbox);
    addSpriteComponent(trap, trapSprite);
    setDataValue(trap, DATA_ATTACK, getDataValue(playerEntity, DATA_ATTACK) + 0.25 * getDataValue(playerEntity, DATA_LEVEL));
    addTag(trap, "Trap");
    addTimerComponent(trap, "dispawn_trap", 2.5f, false);
}

void killChance() {
    int count = 0;
    Entity* enemies = getEntitiesWithTag("Enemy", &count);
    int index = rand() % count - 1;

    if (getDataValue(playerEntity, DATA_LEVEL)/2 >= rand() % 99) {
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
    DataComponent datas = DATA_COMPONENT_DEFAULT;

    // Créer le SpriteComponent pour le barrel
    SpriteComponent barrelSprite = {
        .texture = loadColor(g_renderer, (SDL_Color){255, 0, 0, 64}, size.width, size.height),
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

void explodeBarrel(Entity barrel) {
    // Récupérer la position et la taille du baril
    PositionComponent* barrelPos = getPositionComponent(barrel);
    SizeComponent* barrelSize = getSizeComponent(barrel);

    if (barrelPos == NULL || barrelSize == NULL) {
        printf("Barrel is missing Position or Size component\n");
        return;
    }

    // Définir les limites de la zone d'explosion du baril
    SDL_Rect explosionZone = {
        .x = barrelPos->x,
        .y = barrelPos->y,
        .w = barrelSize->width,
        .h = barrelSize->height
    };

    // Obtenir la valeur de l'attaque du baril
    float damage = (getDataValue(barrel, DATA_ATTACK) * 0.70) * (1 + getDataValue(barrel, DATA_SCORE));
    int count = 0;
    Entity* enemies = getEntitiesWithTag("Enemy", &count);
    // Parcourir toutes les entités et vérifier les ennemis dans la zone
    for (int index = 0; index < count; index++) {
        Entity enemy = enemies[index];
        PositionComponent* enemyPos = getPositionComponent(enemy);
        SizeComponent* enemySize = getSizeComponent(enemy);

        // Définir les limites de l'ennemi
        SDL_Rect enemyZone = {
            .x = enemyPos->x,
            .y = enemyPos->y,
            .w = enemySize->width,
            .h = enemySize->height
        };

        // Vérifier si l'ennemi est dans la zone d'explosion
        if (SDL_HasIntersection(&explosionZone, &enemyZone)) {
            // Infliger des dégâts à l'ennemi
            float health = getDataValue(enemy, DATA_HEALTH) - damage;
            setDataValue(enemy, DATA_HEALTH, health);
            if (health <= 0) {
                Entity* enemyPtr = malloc(sizeof(Entity));
                *enemyPtr = enemy;
                Event eventDeath = {EVENT_TYPE_DEATH, enemyPtr};
                emitEvent(eventDeath);
            }
            printf("Enemy %d hit by barrel explosion for %.2f damage\n", enemy, damage);
        }
    }

    destroyEntity(barrel);
}

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
    SizeComponent size_player = *getSizeComponent(playerEntity);
    PositionComponent position_player = *getPositionComponent(playerEntity);

    PositionComponent position = {
        (position_player.x + size_player.width / 2) - size_poison.width / 2,
        (position_player.y + size_player.height / 2) - size_poison.height / 2
    };
    HitboxComponent hitbox = {0.0f, 0.0f, size_poison.width, size_poison.height, true};
    DataComponent datas = DATA_COMPONENT_DEFAULT;
    SpriteComponent trapSprite = {
        loadColor(g_renderer, (SDL_Color){0, 255, 0, 64}, size_poison.width, size_poison.height),
        (SDL_Rect){0, 0, size_poison.width, size_poison.height}
    };

    addPositionComponent(poison, position);
    addSizeComponent(poison, size_poison);
    addHitboxComponent(poison, hitbox);
    addSpriteComponent(poison, trapSprite);
    addDataComponent(poison, datas);
    setDataValue(poison, DATA_ATTACK, getDataValue(playerEntity, DATA_ATTACK));
    addTag(poison, "Poison");
    addTimerComponent(poison, "apply_poison_tick", 0.250f, true);
}

// Fonction pour ajuster la direction des ennemis vers le "bait"
void adjustEnemyDirection(Entity enemy, PositionComponent baitPosition) {
    PositionComponent* enemyPosition = getPositionComponent(enemy);
    VelocityComponent* enemyVelocity = getVelocityComponent(enemy);

    if (enemyPosition == NULL || enemyVelocity == NULL) {
        return; // Si l'ennemi n'a pas de composant de position ou de vélocité, ignorer
    }

    // Calculer la direction vers le "bait"
    float directionX = baitPosition.x - enemyPosition->x;
    float directionY = baitPosition.y - enemyPosition->y;
    float magnitude = sqrtf(directionX * directionX + directionY * directionY);

    // Normaliser la direction
    if (magnitude != 0) {
        directionX /= magnitude;
        directionY /= magnitude;
    }

    // Définir une vitesse propre à chaque ennemi ou utiliser une valeur fixe
    float speed = sqrtf(enemyVelocity->velocityX * enemyVelocity->velocityX + enemyVelocity->velocityY * enemyVelocity->velocityY);

    // Ajuster la vélocité de l'ennemi pour qu'il se dirige vers le "bait"
    enemyVelocity->velocityX = directionX * speed;
    enemyVelocity->velocityY = directionY * speed;
}
