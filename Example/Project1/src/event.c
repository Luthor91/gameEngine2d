#include "event.h"

void onBullet_Shoot(Event event) {
    int DATA_CAN_SHOOT = getDataType("DATA_CAN_SHOOT");
    int DATA_SPEED = getDataType("DATA_SPEED");
    int DATA_COUNT_SHOOT = getDataType("DATA_COUNT_SHOOT");
    int DATA_LEVEL = getDataType("DATA_LEVEL");
    int DATA_PASSIVE = getDataType("DATA_PASSIVE");
    int DATA_ATTACK = getDataType("DATA_ATTACK");

    if(getDataValue(player_entity, DATA_CAN_SHOOT) == 0.0f) {
        return;
    } else {
        float attack_speed = getDataValue(player_entity, DATA_SPEED);
        addTimerComponent(player_entity, "reloading", attack_speed, false);
        setDataValue(player_entity, DATA_CAN_SHOOT, 0.0f);
        setDataValue(
            player_entity, 
            DATA_COUNT_SHOOT, 
            getDataValue(player_entity, DATA_COUNT_SHOOT)+1.0f
        );
        setDataValue(
            player_entity, 
            DATA_COUNT_SHOOT, 
            getDataValue(player_entity, DATA_COUNT_SHOOT)+1.0f
        );
    }
    
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    Entity bullet = createEntity();

    PositionComponent* player_position = getPositionComponent(player_entity);
    SpriteComponent* player_sprite = getSpriteComponent(player_entity);

    // Calculer le centre du sprite du joueur
    float player_center_x = player_position->x + player_sprite->srcRect.w / 2;
    float player_center_y = player_position->y + player_sprite->srcRect.h / 2;
    
    // Récupérer la position du curseur de la souris  
    PositionComponent bullet_position = {player_center_x, player_center_y};
    VelocityComponent bullet_velocity = VELOCITY_ZERO;
    SizeComponent bullet_size = {12, 12};
    HitboxComponent bullet_hitbox = {0, 0, bullet_size.width, bullet_size.height, true};
    DataComponent bullet_data = DATA_COMPONENT_DEFAULT;

    // Calculer la direction du tir
    float direction_x = mouse_x - player_center_x;
    float direction_y = mouse_y - player_center_y;
    float length = sqrtf(direction_x * direction_x + direction_y * direction_y);
    
    // Normaliser la direction
    if (length != 0) {
        direction_x /= length;
        direction_y /= length;
    }

    bullet_velocity.velocityX = direction_x * 500.0f;
    bullet_velocity.velocityY = direction_y * 500.0f;
    addPositionComponent(bullet, bullet_position);
    addSizeComponent(bullet, bullet_size);
    addVelocityComponent(bullet, bullet_velocity);
    SpriteComponent bullet_sprite = {
        loadColor(g_renderer, COLOR_BLACK, bullet_size.width, bullet_size.height),
        (SDL_Rect){0, 0, bullet_size.width, bullet_size.height}
    };
    addSpriteComponent(bullet, bullet_sprite);
    addHitboxComponent(bullet, bullet_hitbox);
    addDataComponent(bullet, bullet_data);
    setDataValue(bullet, DATA_ATTACK, getDataValue(player_entity, DATA_ATTACK));
    addTag(bullet, "Bullet");

    bool is_third_attack = (int)getDataValue(player_entity, DATA_COUNT_SHOOT) % 3 == 0;
    if (is_third_attack) {
        float level = getDataValue(player_entity, getDataType("DATA_LEVEL"));
        if (level >= 2.0f) {
            amplify_bullet(bullet);
        }
        if (level >= 3.0f) {
            summonSecondBullet(bullet, bullet_velocity.velocityX, bullet_velocity.velocityY);
        }
    }
}

void onBait_Spawn(Event event) {
    int count = 0;
    Entity* baits = getEntitiesWithTag("Bait", &count);
    if (count > 0) return;  

    // Extraire les coordonnées de la souris depuis event->data
    SDL_Point* cursor_position = (SDL_Point*)event.data;
    if (cursor_position == NULL) {
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
        cursor_position->x - size.width / 2, // Centrer la position sur la souris
        cursor_position->y - size.height / 2
    };
    SpriteComponent bait_sprite = {
        loadColor(g_renderer, COLOR_RED, size.width, size.height),
        (SDL_Rect){0, 0, size.width, size.height}
    };

    // Ajouter les composants à l'entité
    addPositionComponent(bait, position);
    addSizeComponent(bait, size);
    addSpriteComponent(bait, bait_sprite);
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

    CollisionData* collision_data = (CollisionData*)event.data;
    Entity enemy = collision_data->entity1;
    Entity bullet = collision_data->entity2;

    int DATA_ATTACK = getDataType("DATA_ATTACK");
    int DATA_HEALTH = getDataType("DATA_HEALTH");

    if (hasDataValue(enemy, DATA_HEALTH)) {
        int health = getDataValue(enemy, DATA_HEALTH) - getDataValue(bullet, DATA_ATTACK);
        setDataValue(enemy, DATA_HEALTH, health);
        handle_damage_received(enemy, health);
    }
    
    PositionComponent bullet_position = *getPositionComponent(bullet);
    setEmitterPosition("Explosion", bullet_position.x, bullet_position.y);
    instanciateParticleEmitter("Explosion");
    disableComponentEntity(bullet);
}

void onBullet_CollideWith_Barrel(Event event) {
    if (!checkCollisionTags(event, "Barrel", "Bullet")) return;
    
    int DATA_ACCUMULATION = getDataType("DATA_ACCUMULATION");

    CollisionData* collision_data = (CollisionData*)event.data; // Note the pointer type
    Entity barrel = collision_data->entity1;
    Entity bullet = collision_data->entity2;
    setDataValue(barrel, DATA_ACCUMULATION, getDataValue(barrel, DATA_ACCUMULATION)+1.0f);

    if (getDataValue(barrel, DATA_ACCUMULATION) >= 5.0f) {
        explodeBarrel(barrel);
    }
    disableComponentEntity(bullet);
}

void onTrap_CollideWith_Enemy(Event event) {
    if (!checkCollisionTags(event, "Enemy", "Trap")) return;

    // Convertir les données de l'événement en pointeur vers CollisionData
    CollisionData* collision_data = (CollisionData*)event.data;
    if (collision_data == NULL) {
        printf("CollisionData is NULL\n");
        return;
    }

    // Récupérer les entités impliquées dans la collision
    Entity enemy = collision_data->entity1;
    Entity trap = collision_data->entity2;

    // Imprimer les tags des entités
    const char* trap_tag = getFirstTag(trap);
    const char* enemy_tag = getFirstTag(enemy);

    int DATA_HEALTH = getDataType("DATA_HEALTH");
    int DATA_ATTACK = getDataType("DATA_ATTACK");


    // Vérifier et mettre à jour la santé de l'ennemi
    if (hasDataValue(enemy, DATA_HEALTH)) {
        int trap_attack = getDataValue(trap, DATA_ATTACK);
        int enemy_health = getDataValue(enemy, DATA_HEALTH) - trap_attack;
        setDataValue(enemy, DATA_HEALTH, enemy_health);
        PositionComponent center_pos = *getCenterPosition(enemy);
        setEmitterPosition("Trap", center_pos.x, center_pos.y);
        instanciateParticleEmitter("Trap");

        // Si la santé de l'ennemi est inférieure ou égale à 0, émettre un événement de mort
        if (enemy_health <= 0) {
            // Créer une nouvelle entité et émettre un événement de mort
            Entity* ptr_entemy = (Entity*)malloc(sizeof(Entity));
            if (ptr_entemy == NULL) {
                printf("Memory allocation failed for enemy entity pointer\n");
                return;
            }
            *ptr_entemy = enemy;
            Event event_death = {getEventType("EVENT_DEATH"), ptr_entemy};
            emitEvent(event_death);
        }
    }

    // Désactiver le trap après la collision
    disableComponentEntity(trap);
}

void onEnemy_CollideWith_Player(Event event) {
    if (!checkCollisionTags(event, "Player", "Enemy")) return;

    // Convertir event.data en pointeur vers CollisionData
    CollisionData* collision_data = (CollisionData*)event.data;

    // Récupérer les entités impliquées dans la collision
    Entity player = collision_data->entity1;
    Entity enemy = collision_data->entity2;

    int DATA_HEALTH = getDataType("DATA_HEALTH");
    int DATA_ATTACK = getDataType("DATA_ATTACK");
    int DATA_LEVEL = getDataType("DATA_LEVEL");

    // Gestion de la collision pour l'ennemi
    if (hasDataValue(player, DATA_HEALTH)) {
        float health = getDataValue(player, DATA_HEALTH) - getDataValue(enemy, DATA_ATTACK);

        setDataValue(player, DATA_HEALTH, health);
        getHitboxComponent(player)->is_active = false;
        addTimerComponent(player, "immunity", 0.250f, false);
        handle_damage_received(player, health);

        float level = getDataValue(player, DATA_LEVEL);
        if (level >= 7.0f) {
            summonPoison();
        }
        if (level >= 8.0f) {
            removeEventListener(getEventType("EVENT_RIGHT_MOUSECLICK"), onBait_Spawn);
            addEventListener(getEventType("EVENT_RIGHT_MOUSECLICK"), onBait_Spawn);
        }

        
    }
    disableComponentEntity(enemy);
}

void onLeveling_Up(Event event) {   
    if (!hasAnyTag(event, "Player", NULL)) return;

    Entity entity = *(Entity*)event.data; 
    
    int DATA_LEVEL = getDataType("DATA_LEVEL");
    int DATA_ATTACK = getDataType("DATA_ATTACK");
    int DATA_HEALTH = getDataType("DATA_HEALTH");
    int DATA_SPEED = getDataType("DATA_SPEED");

    if (getDataValue(entity, DATA_LEVEL) >= 10.0f) return;

    setDataValue(entity, DATA_LEVEL, getDataValue(entity, DATA_LEVEL)+1.0f);
    setDataValue(entity, DATA_ATTACK, getDataValue(entity, DATA_ATTACK)*1.25);
    setDataValue(entity, DATA_HEALTH, getDataValue(entity, DATA_HEALTH)*1.1);
    setDataValue(entity, DATA_SPEED, getDataValue(entity, DATA_SPEED)*0.85);

    float level = getDataValue(entity, DATA_LEVEL);
    if (level == 6.0f) {
        addTimerComponent(entity, "spawn_barrel", 15.0f, true);
    } 

    printf("Leveling up to %.1f !\n\tAttack : %f\n\tHealth : %f\n\tAttack Speed : %f attacks per second\n", 
        getDataValue(entity, DATA_LEVEL),  getDataValue(entity, DATA_ATTACK),
        getDataValue(entity, DATA_HEALTH), 1.0f/getDataValue(entity, DATA_SPEED)
    );
}

void onDeath(Event event) {
    if (!hasAnyTag(event, "Player", "Enemy", NULL)) return;

    Entity* ptr_entity = (Entity*)event.data;
    Entity entity = *ptr_entity; 

    if (entity == player_entity) {
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
    PositionComponent* entity_position = getPositionComponent(entity);
    SizeComponent* entity_size = getSizeComponent(entity);
    
    // Vérifiez que les composants sont valides
    if (entity_position == NULL || entity_size == NULL) {
        printf("Position or size component is NULL\n");
        return;
    }

    // Calculer la position de la mort
    PositionComponent death_position = *getCenterPosition(entity);

    int DATA_KILLED = getDataType("DATA_KILLED");
    int DATA_LEVEL = getDataType("DATA_LEVEL");

    setDataValue(
        player_entity, 
        DATA_KILLED, 
        getDataValue(player_entity, DATA_KILLED)+1.0f
    );

    // Vérifier si le joueur doit monter de niveau
    bool should_level_up = (int)getDataValue(player_entity, DATA_KILLED) % 1 == 0;
    if (should_level_up) {
        Event levelUpEvent = {getEventType("EVENT_LEVEL_UP"), &player_entity};
        emitEvent(levelUpEvent);
    }

    float level = getDataValue(player_entity, DATA_LEVEL);
    if (level >= 4.0) {
        summonTrap(death_position);
    }
    if (level >= 5.0) {
        killChance();
    }

    disableComponentEntity(entity);
}

void onDamaged(Event event) {
    if (event.data == NULL) {
        fprintf(stderr, "event.data is NULL\n");
        return;
    }

    Entity entity = *(Entity*)event.data; 

    int DATA_MAX_HEALTH = getDataType("DATA_MAX_HEALTH");
    int DATA_HEALTH = getDataType("DATA_HEALTH");
    
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

