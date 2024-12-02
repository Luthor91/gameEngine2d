#include "event.h"

void onBullet_Shoot(Event event) {
    // Prérequis pour tirer
    int DATA_CAN_SHOOT = getDataType("DATA_CAN_SHOOT");
    float can_shoot = getDataValue(player_entity, DATA_CAN_SHOOT);
    if (can_shoot == 0.0f) return;
    // Variables pour gérer les données du joueur
    int DATA_SPEED = getDataType("DATA_SPEED");
    int DATA_COUNT_SHOOT = getDataType("DATA_COUNT_SHOOT");
    int DATA_LEVEL = getDataType("DATA_LEVEL");
    int DATA_ATTACK = getDataType("DATA_ATTACK");

    // Mise à jour des données du joueur
    float attack_speed = getDataValue(player_entity, DATA_SPEED);
    int count_bullet = (int)getDataValue(player_entity, DATA_COUNT_SHOOT);
    float level = getDataValue(player_entity, DATA_LEVEL);
    float attack_value = getDataValue(player_entity, DATA_ATTACK);

    // Mise en place du rechargement
    addTimerComponent(player_entity, "reloading", attack_speed, false);
    setDataValue(player_entity, DATA_CAN_SHOOT, 0.0f);
    setDataValue(player_entity, DATA_COUNT_SHOOT, count_bullet + 1.0f);

    // Récupération de la position de la souris
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    // Calcul de la direction du tir
    PositionComponent* player_position = getCenterPosition(player_entity);
    float direction_x = mouse_x - player_position->x;
    float direction_y = mouse_y - player_position->y;
    float length = sqrtf(direction_x * direction_x + direction_y * direction_y);
    
    // Normalisation de la direction
    if (length != 0) {
        direction_x /= length;
        direction_y /= length;
    }

    // Création de l'entité bullet après avoir vérifié les conditions nécessaires
    Entity bullet = createEntity();
    if (!isEntityValid(bullet)) return;

    // Initialisation des composants du bullet
    PositionComponent bullet_position = {player_position->x, player_position->y};
    VelocityComponent bullet_velocity = {direction_x * 400.0f, direction_y * 400.0f};
    SizeComponent bullet_size = {12, 12};
    HitboxComponent bullet_hitbox = {0, 0, bullet_size.width, bullet_size.height, true};
    SpriteComponent bullet_sprite = {
        loadColor(game.renderer, COLOR_BLACK, bullet_size.width, bullet_size.height),
        (SDL_Rect){0, 0, bullet_size.width, bullet_size.height}
    };
    DataComponent bullet_data = DATA_COMPONENT_DEFAULT;

    // Ajout des composants à l'entité bullet
    addPositionComponent(bullet, bullet_position);
    addSizeComponent(bullet, bullet_size);
    addVelocityComponent(bullet, bullet_velocity);
    addSpriteComponent(bullet, bullet_sprite);
    addHitboxComponent(bullet, bullet_hitbox);
    addDataComponent(bullet, bullet_data);
    setDataValue(bullet, DATA_ATTACK, attack_value);
    addTag(bullet, "Bullet");
    addEntityToOutOfBoundsCleanup(bullet);

    // Gestion des effets basés sur le niveau et le nombre de tirs
    bool is_third_attack = count_bullet % 3 == 0;
    bool is_fifth_attack = count_bullet % 5 == 0;

    if (is_fifth_attack && level >= 2.0f) {
        amplify_bullet(bullet);
    } else if (is_third_attack && level >= 3.0f) {
        summonSecondBullet(bullet, bullet_velocity.x, bullet_velocity.y);
    }
}

void onBait_Spawn(Event event) {
    int count = 0;
    Entity* baits = getEntitiesWithTag("Bait", &count);
    if (count > 0) return;  

    // Extraire les coordonnées de la souris depuis event->data
    SDL_Point* cursor_position = (SDL_Point*)event.data;
    if (cursor_position == NULL) return;

    // Créer une nouvelle entité "bait"
    Entity bait = createEntity();
    if (bait == INVALID_ENTITY_ID)  return;

    // Configurer les composants pour l'entité "bait"
    SizeComponent size = {20.0f, 20.0f};
    PositionComponent position = {
        cursor_position->x - size.width / 2, // Centrer la position sur la souris
        cursor_position->y - size.height / 2
    };
    SpriteComponent bait_sprite = {
        loadColor(game.renderer, COLOR_PURPLE, size.width, size.height),
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
    if (count < 0) return;  

    for (int index = 0; index < count; index++) {
        Entity enemy = enemies[index];
        adjustEnemyDirection(enemy, position); // Ajuster la direction vers le "bait"
    }

    // Ajouter un timer pour détruire le "bait" après un certain temps
    addTimerComponent(bait, "dispawn_bait", 2.5f, false);
}

void onBullet_CollideWith_Enemy(Event event) {
    if (!checkCollisionTags(event, "Enemy", "Bullet")) return;
    printf("bullet collided with enemy\n");
    CollisionData* collision_data = (CollisionData*)event.data;
    Entity enemy = collision_data->entity1;
    Entity bullet = collision_data->entity2;

    int DATA_ATTACK = getDataType("DATA_ATTACK");
    int DATA_HEALTH = getDataType("DATA_HEALTH");

    if (!hasDataValue(enemy, DATA_HEALTH) || !hasDataValue(bullet, DATA_ATTACK)) return;
    if (!hasPositionComponent(bullet) || !hasSizeComponent(bullet)) return;
    if (!hasPositionComponent(enemy) || !hasSizeComponent(enemy)) return;

    float health_enemy =  getDataValue(enemy, DATA_HEALTH);
    float bullet_attack = getDataValue(bullet, DATA_ATTACK);
    int health = health_enemy - bullet_attack;

    setDataValue(enemy, DATA_HEALTH, health);
    handle_damage_received(enemy, health);

    PositionComponent* bullet_position = getCenterPosition(bullet);
    setEmitterPosition("Explosion", bullet_position->x, bullet_position->y);
    instanciateParticleEmitter("Explosion");
    activateEmitter("c_Explosion");
    
    disableComponentEntity(bullet);
}

void onBullet_CollideWith_Barrel(Event event) {
    if (!checkCollisionTags(event, "Barrel", "Bullet")) return;
    
    int DATA_ACCUMULATION = getDataType("DATA_ACCUMULATION");

    CollisionData* collision_data = (CollisionData*)event.data; // Note the pointer type
    Entity barrel = collision_data->entity1;
    Entity bullet = collision_data->entity2;
    if (barrel == INVALID_ENTITY_ID || bullet == INVALID_ENTITY_ID) return;

    float data_accumulation = getDataValue(barrel, DATA_ACCUMULATION) + 1.0f;
    setDataValue(barrel, DATA_ACCUMULATION, data_accumulation);

    SizeComponent* barrel_size = getSizeComponent(barrel);
    PositionComponent* barrel_position = getPositionComponent(barrel);
    HitboxComponent* barrel_hitbox = getHitboxComponent(barrel);
    SpriteComponent* barrel_sprite = getSpriteComponent(barrel);

    float size_multiplier = 1.2f;
    if (data_accumulation ==  5.0f) size_multiplier *= 1.5f;
    
    float previous_barrel_height = barrel_size->height;
    float previous_barrel_width = barrel_size->width;
    
    
    barrel_size->height *= size_multiplier;
    barrel_size->width *= size_multiplier;
    barrel_hitbox->height = barrel_size->height;
    barrel_hitbox->width = barrel_size->width;
    barrel_sprite->srcRect.h = barrel_size->height;
    barrel_sprite->srcRect.w = barrel_size->width;

    float delta_height = ( (barrel_size->width - previous_barrel_height) / 2);
    float delta_width = ( (barrel_size->height - previous_barrel_width) / 2);

    barrel_position->x = barrel_position->x - delta_height;
    barrel_position->y = barrel_position->y - delta_width;

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

    Entity enemy = collision_data->entity1;
    Entity trap = collision_data->entity2;

    // Imprimer les tags des entités
    const char* trap_tag = getFirstTag(trap);
    const char* enemy_tag = getFirstTag(enemy);

    int DATA_HEALTH = getDataType("DATA_HEALTH");
    int DATA_ATTACK = getDataType("DATA_ATTACK");

    // Vérifier et mettre à jour la santé de l'ennemi
    if (!hasDataValue(enemy, DATA_HEALTH) || !hasDataValue(trap, DATA_ATTACK)) return;
    int trap_attack = getDataValue(trap, DATA_ATTACK);
    int enemy_health = getDataValue(enemy, DATA_HEALTH) - trap_attack;

    PositionComponent* center_pos = getCenterPosition(enemy);

    setDataValue(enemy, DATA_HEALTH, enemy_health);
    setEmitterPosition("Trap", center_pos->x, center_pos->y);
    instanciateParticleEmitter("Trap");
    activateEmitter("c_Trap");
    handle_damage_received(enemy, enemy_health);

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
    if (!hasDataValue(player, DATA_HEALTH)) return;
    
    float health = getDataValue(player, DATA_HEALTH) - getDataValue(enemy, DATA_ATTACK);
    setDataValue(player, DATA_HEALTH, health);
    getHitboxComponent(player)->is_active = false;
    addTimerComponent(player, "immunity", 0.250f, false);
    handle_damage_received(player, health);

    if (!hasDataValue(player, DATA_LEVEL)) return;
    float level = getDataValue(player, DATA_LEVEL);
    if (level >= 7.0f) {
        summonPoison();
    }

    disableComponentEntity(enemy);
}

void onLeveling_Up(Event event) {
    if (!isEventName(event, "level_up")) return;

    Entity *entity_ptr = (Entity *)event.data;
    if (entity_ptr == NULL) {
        printf("onLeveling_Up: Entity corrupted\n");
    }
    Entity entity = *entity_ptr;

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
        addTimerComponent(entity, "spawn_barrel", 7.5f, true);
    }        
    if (level == 8.0f) {
        addEventListener(getEventType("EVENT_RIGHT_MOUSECLICK"), onBait_Spawn);
    }

    printf("Leveling up to %.1f !\n\tAttack : %f\n\tHealth : %f\n\tAttack Speed : %f attacks per second\n", 
        getDataValue(entity, DATA_LEVEL),  getDataValue(entity, DATA_ATTACK),
        getDataValue(entity, DATA_HEALTH), 1.0f/getDataValue(entity, DATA_SPEED)
    );
}

void onDeathPlayer(Event event) {
    if (!hasAnyTag(event, "Player", NULL) && !isEventName(event, "death")) return;

    Entity* ptr_entity = (Entity*)event.data;
    Entity entity = *ptr_entity; 

    if (!hasPositionComponent(entity) || !hasSizeComponent(entity)) return;    

    disableComponentEntitiesFromRange(0, MAX_ENTITIES);
    Entity end_screen = createEntity();
    PositionComponent pos = POSITION_ZERO;
    SpriteComponent sprite = {
        loadTexture("Assets/TowerDefense/EndScreen.png", game.renderer), 
        (SDL_Rect){0, 0, game.window_width, game.window_height}
    };

    addPositionComponent(end_screen, pos);
    addSpriteComponent(end_screen, sprite);
}

void onDeathEnemy(Event event) {
    if (!hasAnyTag(event, "Enemy", NULL) && !isEventName(event, "death")) return;

    Entity* ptr_entity = (Entity*)event.data;
    Entity entity = *ptr_entity; 

    if (!hasPositionComponent(entity) || !hasSizeComponent(entity)) return;    

    int DATA_KILLED = getDataType("DATA_KILLED");
    int DATA_LEVEL = getDataType("DATA_LEVEL");

    setDataValue(
        player_entity, 
        DATA_KILLED, 
        getDataValue(player_entity, DATA_KILLED)+1.0f
    );

    PositionComponent* death_position = getCenterPosition(entity);
    float level = getDataValue(player_entity, DATA_LEVEL);

    if (level >= 4.0) {
        summonTrap(*death_position);
    }

    if (level >= 5.0) {
        killChance();
    }

    bool should_level_up = (int)getDataValue(player_entity, DATA_KILLED) % 2 == 0;
    if (should_level_up) {
        Event level_up = Event_Create(getEventType("EVENT_LEVEL_UP"), "level_up");

        Entity *player_entity_ptr = malloc(sizeof(Entity));
        if (player_entity_ptr == NULL) {
            fprintf(stderr, "Erreur : Impossible d'allouer de la mémoire pour player_entity_ptr\n");
            exit(EXIT_FAILURE);
        }

        *player_entity_ptr = player_entity;
        level_up.data = (void *)player_entity_ptr;

        emitEvent(level_up);
    }
    
    printf("onDeathEnemy: Entity killed : %ld\n", entity);
    disableComponentEntity(entity);
}

void onDamaged(Event event) {
    if (!isEventName(event, "damaged")) return;

    Entity entity = *(Entity*)event.data;
    if (entity == INVALID_ENTITY_ID) return;
    
    int DATA_MAX_HEALTH = getDataType("DATA_MAX_HEALTH");
    int DATA_HEALTH = getDataType("DATA_HEALTH");
    
    // Récupérer les valeurs de santé actuelle et maximale
    if (!hasDataValue(entity, DATA_HEALTH) || !hasDataValue(entity, DATA_MAX_HEALTH)) return;
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
        SDL_Texture* texture = loadTexture(sprite_file, game.renderer);

        // Obtenir la taille du joueur (assumant que getSizeComponent retourne un pointeur valide)
        SizeComponent* size = getSizeComponent(entity);

        // Créer un SpriteComponent avec la nouvelle texture
        SpriteComponent sprite = {
            texture, 
            (SDL_Rect){0, 0, (int)size->width, (int)size->height}
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
        SDL_Texture* texture = loadTexture(sprite_file, game.renderer);

        // Obtenir la taille de l'ennemi (assumant que getSizeComponent retourne un pointeur valide)
        SizeComponent* size = getSizeComponent(entity);

        // Créer un SpriteComponent avec la nouvelle texture
        SpriteComponent sprite = {
            texture, 
            (SDL_Rect){0, 0, (int)size->width, (int)size->height}
        };

        // Ajouter ou remplacer le composant de sprite de l'ennemi
        addSpriteComponent(entity, sprite);
        
    }
}
