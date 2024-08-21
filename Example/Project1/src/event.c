#include "event.h"

void onBullet_Shoot(Event event) {
    if(getDataValue(playerEntity, DATA_CAPABLE) == 0.0f) {
        return;
    } else {
        float attack_speed = getDataValue(playerEntity, DATA_SPEED);
        addTimerComponent(playerEntity, "reloading", attack_speed, false);
        setDataValue(playerEntity, DATA_CAPABLE, 0.0f);
        setDataValue(
            playerEntity, 
            DATA_COUNT_SHOOT, 
            getDataValue(playerEntity, DATA_COUNT_SHOOT)+1.0f
        );
        setDataValue(
            playerEntity, 
            DATA_COUNT_SHOOT, 
            getDataValue(playerEntity, DATA_COUNT_SHOOT)+1.0f
        );
    }

    float coeff_passive = 1.0f;
    bool is_third_attack = (int)getDataValue(playerEntity, DATA_COUNT_SHOOT) % 3 == 0;
    if (getDataValue(playerEntity, DATA_LEVEL) >= 2.0 && is_third_attack) {
        setDataValue(playerEntity, DATA_COUNT_SHOOT, 0.0f);
        coeff_passive = getDataValue(playerEntity, DATA_PASSIVE);
    }
        
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    Entity bullet = createEntity();

    PositionComponent* playerPosition = getPositionComponent(playerEntity);
    SpriteComponent* playerSprite = getSpriteComponent(playerEntity);

    // Calculer le centre du sprite du joueur
    float playerCenterX = playerPosition->x + playerSprite->srcRect.w / 2;
    float playerCenterY = playerPosition->y + playerSprite->srcRect.h / 2;
    
    // Récupérer la position du curseur de la souris  
    PositionComponent bulletPosition = {playerCenterX, playerCenterY};
    VelocityComponent bulletVelocity = VELOCITY_ZERO;
    SizeComponent bulletSize = {12*coeff_passive, 12*coeff_passive};
    HitboxComponent bulletHitbox = {0, 0, bulletSize.width, bulletSize.height, true};
    DataComponent bulletData = DATA_COMPONENT_DEFAULT;

    // Calculer la direction du tir
    float directionX = mouseX - playerCenterX;
    float directionY = mouseY - playerCenterY;
    float length = sqrtf(directionX * directionX + directionY * directionY);
    
    // Normaliser la direction
    if (length != 0) {
        directionX /= length;
        directionY /= length;
    }

    bulletVelocity.velocityX = directionX * 500.0f * coeff_passive;
    bulletVelocity.velocityY = directionY * 500.0f * coeff_passive;
    addPositionComponent(bullet, bulletPosition);
    addSizeComponent(bullet, bulletSize);
    addVelocityComponent(bullet, bulletVelocity);
    SpriteComponent bulletSprite = {
        loadColor(g_renderer, coeff_passive == 2.0 ? COLOR_RED : COLOR_BLACK, bulletSize.width, bulletSize.height),
        (SDL_Rect){0, 0, bulletSize.width, bulletSize.height}
    };
    addSpriteComponent(bullet, bulletSprite);
    addHitboxComponent(bullet, bulletHitbox);
    addDataComponent(bullet, bulletData);
    setDataValue(bullet, DATA_ATTACK, getDataValue(playerEntity, DATA_ATTACK) * coeff_passive);
    addTag(bullet, "Bullet");

    if ((int)getDataValue(playerEntity, DATA_COUNT_SHOOT) % 3 == 0 && getDataValue(playerEntity, DATA_LEVEL) >= 3.0) {
        summonSecondBullet(bullet, directionX, directionY, coeff_passive);
    }
}

void onBait_Spawn(Event event) {
    int count = 0;
    Entity* baits = getEntitiesWithTag("Bait", &count);
    if (count > 0) return;  

    // Extraire les coordonnées de la souris depuis event->data
    SDL_Point* cursorPos = (SDL_Point*)event.data;
    if (cursorPos == NULL) {
        printf("Cursor position data is null\n");
        return;
    }

    // Créer une nouvelle entité "bait"
    Entity bait = createEntity();
    if (bait == INVALID_ENTITY_ID) {
        printf("Failed to create bait entity\n");
        return;
    }

    // Configurer les composants pour l'entité "bait"
    SizeComponent size = {20.0f, 20.0f}; // Taille du bait, par exemple 20x20
    PositionComponent position = {
        cursorPos->x - size.width / 2, // Centrer la position sur la souris
        cursorPos->y - size.height / 2
    };
    SpriteComponent baitSprite = {
        loadColor(g_renderer, COLOR_RED, size.width, size.height),
        (SDL_Rect){0, 0, size.width, size.height}
    };

    // Ajouter les composants à l'entité
    addPositionComponent(bait, position);
    addSizeComponent(bait, size);
    addSpriteComponent(bait, baitSprite);
    addTag(bait, "Bait");

    // Faire changer la direction des ennemis vers le "bait"
    count = 0;
    Entity* enemies = getEntitiesWithTag("Enemy", &count);
    for (int index = 0; index < count; index++) {
        Entity enemy = enemies[index];
        adjustEnemyDirection(enemy, position); // Ajuster la direction vers le "bait"
    }

    // Ajouter un timer pour détruire le "bait" après un certain temps
    addTimerComponent(bait, "dispawn_bait", 2.5f, false);
}

void onBullet_CollideWith_Enemy(Event event) {
    if (!checkCollisionTags(event, "Enemy", "Bullet")) return;

    CollisionData* collisionData = (CollisionData*)event.data;
    Entity enemy = collisionData->entity1;
    Entity bullet = collisionData->entity2;

    if (hasDataValue(enemy, DATA_HEALTH)) {
        int health = getDataValue(enemy, DATA_HEALTH) - getDataValue(bullet, DATA_ATTACK);
        setDataValue(enemy, DATA_HEALTH, health);

        // Si la santé de l'ennemi tombe à 0 ou en dessous, émettre un événement de mort
        Entity* enemy_ptr = malloc(sizeof(Entity));
        *enemy_ptr = enemy;
        if (health <= 0) {
            Event eventDeath = {EVENT_TYPE_DEATH, enemy_ptr};
            emitEvent(eventDeath);
        } else {
            Event event_damaged = {EVENT_TYPE_INFO, enemy_ptr};
            emitEvent(event_damaged);
        }
    }
    
    PositionComponent positionBullet = *getPositionComponent(bullet);
    setEmitterPosition("Explosion", positionBullet.x, positionBullet.y);
    instanciateParticleEmitter("Explosion");
    disableComponentEntity(bullet);
}

void onBullet_CollideWith_Barrel(Event event) {
    if (!checkCollisionTags(event, "Barrel", "Bullet")) return;
    CollisionData* collisionData = (CollisionData*)event.data; // Note the pointer type
    Entity barrel = collisionData->entity1;
    Entity bullet = collisionData->entity2;
    setDataValue(barrel, DATA_SCORE, getDataValue(barrel, DATA_SCORE)+1.0f);

    if (getDataValue(barrel, DATA_SCORE) >= 5.0f) {
        explodeBarrel(barrel);
    }
    disableComponentEntity(bullet);
}

void onTrap_CollideWith_Enemy(Event event) {
    if (!checkCollisionTags(event, "Enemy", "Trap")) return;

    // Convertir les données de l'événement en pointeur vers CollisionData
    CollisionData* collisionData = (CollisionData*)event.data;
    if (collisionData == NULL) {
        printf("CollisionData is NULL\n");
        return;
    }

    // Récupérer les entités impliquées dans la collision
    Entity enemy = collisionData->entity1;
    Entity trap = collisionData->entity2;

    // Imprimer les tags des entités
    const char* trapTag = getFirstTag(trap);
    const char* enemyTag = getFirstTag(enemy);

    // Vérifier et mettre à jour la santé de l'ennemi
    if (hasDataValue(enemy, DATA_HEALTH)) {
        int trapAttack = getDataValue(trap, DATA_ATTACK);
        int enemyHealth = getDataValue(enemy, DATA_HEALTH) - trapAttack;
        setDataValue(enemy, DATA_HEALTH, enemyHealth);
        PositionComponent center_pos = *getCenterPosition(enemy);
        setEmitterPosition("Trap", center_pos.x, center_pos.y);
        instanciateParticleEmitter("Trap");

        // Si la santé de l'ennemi est inférieure ou égale à 0, émettre un événement de mort
        if (enemyHealth <= 0) {
            // Créer une nouvelle entité et émettre un événement de mort
            Entity* enemyEntityPtr = (Entity*)malloc(sizeof(Entity));
            if (enemyEntityPtr == NULL) {
                printf("Memory allocation failed for enemy entity pointer\n");
                return;
            }
            *enemyEntityPtr = enemy;
            Event eventDeath = {EVENT_TYPE_DEATH, enemyEntityPtr};
            emitEvent(eventDeath);
        }
    }

    // Désactiver le trap après la collision
    disableComponentEntity(trap);
}

void onEnemy_CollideWith_Player(Event event) {
    if (!checkCollisionTags(event, "Player", "Enemy")) return;

    // Convertir event.data en pointeur vers CollisionData
    CollisionData* collisionData = (CollisionData*)event.data;

    // Récupérer les entités impliquées dans la collision
    Entity player = collisionData->entity1;
    Entity enemy = collisionData->entity2;

    // Gestion de la collision pour l'ennemi
    if (hasDataValue(player, DATA_HEALTH)) {
        float health = getDataValue(player, DATA_HEALTH) - getDataValue(enemy, DATA_ATTACK);

        setDataValue(player, DATA_HEALTH, health);
        getHitboxComponent(player)->is_active = false;
        addTimerComponent(player, "immunity", 0.250f, false);

        Entity* player_ptr = malloc(sizeof(Entity));
        *player_ptr = player;
        if (health <= 0) {
            Event eventDeath = {EVENT_TYPE_DEATH, player_ptr};
            emitEvent(eventDeath);
        } else {
            Event event_damaged = {EVENT_TYPE_INFO, player_ptr};
            emitEvent(event_damaged);
        }

        if (getDataValue(player, DATA_LEVEL) >= 7.0f) {
            summonPoison();
        }
        if (getDataValue(player, DATA_LEVEL) >= 8.0f) {
            addEventListener(EVENT_TYPE_RIGHT_MOUSECLICK, onBait_Spawn);
        }

        
    }
    disableComponentEntity(enemy);
}

void onLeveling_Up(Event event) {   
    if (!hasAnyTag(event, "Player", NULL)) return;

    Entity entity = *(Entity*)event.data; 
    setDataValue(entity, DATA_LEVEL, getDataValue(entity, DATA_LEVEL)+1.0f);
    setDataValue(entity, DATA_ATTACK, getDataValue(entity, DATA_ATTACK)*1.25);
    setDataValue(entity, DATA_HEALTH, getDataValue(entity, DATA_HEALTH)*1.1);
    setDataValue(entity, DATA_SPEED, getDataValue(entity, DATA_SPEED)*0.75);

    if (getDataValue(entity, DATA_LEVEL) >= 6.0f) {
        addTimerComponent(entity, "spawn_barrel", 15.0f, true);
    } 

    printf("Leveling up to %.1f !\n\tAttack : %f\n\tHealth : %f\n\tAttack Speed : %f attacks per second\n", 
        getDataValue(entity, DATA_LEVEL),  getDataValue(entity, DATA_ATTACK),
        getDataValue(entity, DATA_HEALTH), 1.0f/getDataValue(entity, DATA_SPEED)
    );
}

void onDeath(Event event) {
    if (!hasAnyTag(event, "Player", "Enemy", NULL)) return;

    Entity* entityPtr = (Entity*)event.data;
    Entity entity = *entityPtr; 

    if (entity == playerEntity) {
        disableComponentEntitiesFromRange(0, MAX_ENTITIES);
        Entity end_screen = createEntity();
        PositionComponent pos = POSITION_ZERO;
        addPositionComponent(end_screen, pos);
        SpriteComponent sprite = {
            loadTexture("Assets/TowerDefense/EndScreen.png", g_renderer), 
            (SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}
        };
        addSpriteComponent(end_screen, sprite);
        return;
    }

    // Obtenir les composants nécessaires pour la position
    PositionComponent* posComponent = getPositionComponent(entity);
    SizeComponent* sizeComponent = getSizeComponent(entity);
    
    // Vérifiez que les composants sont valides
    if (posComponent == NULL || sizeComponent == NULL) {
        printf("Position or size component is NULL\n");
        return;
    }

    // Calculer la position de la mort
    PositionComponent deathPosition = {
        posComponent->x + sizeComponent->width / 2,
        posComponent->y + sizeComponent->height / 2
    };

    // Désactiver l'entité
    disableComponentEntity(entity);
    setDataValue(
        entity, 
        DATA_SCORE, 
        getDataValue(entity, DATA_SCORE)+1.0f
    );

    // Vérifier si le joueur doit monter de niveau
    if ((int)getDataValue(entity, DATA_SCORE) % 5 == 0) {
        Event levelUpEvent = {EVENT_TYPE_LEVEL_UP, &playerEntity};
        emitEvent(levelUpEvent);
    }
    if (getDataValue(playerEntity, DATA_LEVEL) >= 4.0) {
        summonTrap(deathPosition);
    } else if (getDataValue(playerEntity, DATA_LEVEL) >= 5.0) {
        killChance();
    }
}

void onDamaged(Event event) {
    if (event.data == NULL) {
        fprintf(stderr, "event.data is NULL\n");
        return;
    }

    Entity entity = *(Entity*)event.data; 
    printf("entity : %d\n", entity);

    // Récupérer les valeurs de santé actuelle et maximale
    float curr_health = getDataValue(entity, DATA_HEALTH);
    float max_health = getDataValue(entity, DATA_MAX_HEALTH);
    float health_percentage = (curr_health / max_health) * 100.0f;

    const char* sprite_file = NULL;

    // Vérification du tag pour distinguer le joueur de l'ennemi
    if (hasTag(entity, "Player")) {
        // Déterminer le sprite à charger en fonction du pourcentage de santé
        if (health_percentage > 70.0f) {
            sprite_file = "Assets/TowerDefense/TurretFullHealth.png";
        } else if (health_percentage > 40.0f) {
            sprite_file = "Assets/TowerDefense/TurretMidHealth.png";
        } else {
            sprite_file = "Assets/TowerDefense/TurretLowHealth.png";
        }

        // Charger la texture correspondante
        SDL_Texture* texture = loadTexture(sprite_file, g_renderer);

        // Obtenir la taille du joueur (assumant que getSizeComponent retourne un pointeur valide)
        SizeComponent size = *getSizeComponent(entity);

        // Créer un SpriteComponent avec la nouvelle texture
        SpriteComponent sprite = {
            texture, 
            (SDL_Rect){0, 0, (int)size.width, (int)size.height}
        };

        // Ajouter ou remplacer le composant de sprite du joueur
        addSpriteComponent(entity, sprite);

    } else if (hasTag(entity, "Enemy")) {
        // Déterminer le sprite à charger en fonction du pourcentage de santé
        if (health_percentage > 70.0f) {
            sprite_file = "Assets/TowerDefense/EnemyFullHealth.png";
        } else if (health_percentage > 40.0f) {
            sprite_file = "Assets/TowerDefense/EnemyMidHealth.png";
        } else {
            sprite_file = "Assets/TowerDefense/EnemyLowHealth.png";
        }

        // Charger la texture correspondante
        SDL_Texture* texture = loadTexture(sprite_file, g_renderer);

        // Obtenir la taille de l'ennemi (assumant que getSizeComponent retourne un pointeur valide)
        SizeComponent size = *getSizeComponent(entity);

        // Créer un SpriteComponent avec la nouvelle texture
        SpriteComponent sprite = {
            texture, 
            (SDL_Rect){0, 0, (int)size.width, (int)size.height}
        };

        // Ajouter ou remplacer le composant de sprite de l'ennemi
        addSpriteComponent(entity, sprite);
        
    }
}

