#include "../../Core/core.h"
#include "src/global.h"

int main(int argc, char* argv[]) {
    Init_All();

    //registerCleanupFunction(cleanupOutOfBoundsEntities);

    EventType EVENT_LEFT_MOUSECLICK = getEventType("EVENT_LEFT_MOUSECLICK");
    EventType EVENT_LEVEL_UP = getEventType("EVENT_LEVEL_UP");
    EventType EVENT_DEATH = getEventType("EVENT_DEATH");
    EventType EVENT_INFO = getEventType("EVENT_INFO");
    EventType EVENT_COLLIDE = getEventType("EVENT_COLLIDE");
    EventType EVENT_TIMER_EXPIRED = getEventType("EVENT_TIMER_EXPIRED");

    // Ajouter des listeners pour les événements
    addEventListener(EVENT_LEFT_MOUSECLICK, onBullet_Shoot);
    addEventListener(EVENT_LEVEL_UP, onLeveling_Up);
    addEventListener(EVENT_DEATH, onDeathPlayer);
    addEventListener(EVENT_DEATH, onDeathEnemy);
    addEventListener(EVENT_INFO, onDamaged);

    addEventListener(EVENT_COLLIDE, onBullet_CollideWith_Enemy);
    addEventListener(EVENT_COLLIDE, onBullet_CollideWith_Barrel);
    addEventListener(EVENT_COLLIDE, onTrap_CollideWith_Enemy);
    addEventListener(EVENT_COLLIDE, onEnemy_CollideWith_Player);

    addEventListener(EVENT_TIMER_EXPIRED, uponReloading);
    addEventListener(EVENT_TIMER_EXPIRED, uponInvincibilityFinished);

    addEventListener(EVENT_TIMER_EXPIRED, uponIncreasingDifficulty);
    addEventListener(EVENT_TIMER_EXPIRED, uponApplyingPoisonTicks);

    addEventListener(EVENT_TIMER_EXPIRED, uponSpawnEnemies);
    addEventListener(EVENT_TIMER_EXPIRED, uponSpawnBarrel);
    addEventListener(EVENT_TIMER_EXPIRED, uponSpawnPoison);

    addEventListener(EVENT_TIMER_EXPIRED, uponDispawnTrap);
    addEventListener(EVENT_TIMER_EXPIRED, uponDispawnBarrel);
    addEventListener(EVENT_TIMER_EXPIRED, uponDispawnBait);

    int DATA_HEALTH = addDataType("DATA_HEALTH");
    int DATA_MAX_HEALTH = addDataType("DATA_MAX_HEALTH");
    int DATA_SPEED = addDataType("DATA_SPEED");
    int DATA_ATTACK = addDataType("DATA_ATTACK");
    int DATA_PASSIVE = addDataType("DATA_PASSIVE");
    int DATA_LEVEL = addDataType("DATA_LEVEL");
    int DATA_KILLED =  addDataType("DATA_KILLED");
    int DATA_DIFFICULTY =  addDataType("DATA_DIFFICULTY");
    int DATA_CAN_SHOOT = addDataType("DATA_CAN_SHOOT");
    int DATA_COUNT_SHOOT = addDataType("DATA_COUNT_SHOOT");
    int DATA_ACCUMULATION = addDataType("DATA_ACCUMULATION");
    int DATA_MAX_PROC = addDataType("DATA_MAX_PROC");
     
    // Définition du fond d'écran
    Entity background = createEntity();
    PositionComponent background_position = POSITION_ZERO;
    SpriteComponent background_sprite = {
        loadTexture("Assets/TowerDefense/BackgroundSpace.png", game.renderer), 
        (SDL_Rect){0, 0, game.window_width, game.window_height}
    };

    addPositionComponent(background, background_position);
    addSpriteComponent(background, background_sprite);

    // Définition du player
    player_entity = createEntity();
    PositionComponent player_position = {game.window_width/2 - 16, game.window_height/2};
    SizeComponent player_size = {32, 32};
    HitboxComponent player_hitbox = { 0, 0, player_size.width, player_size.height, true};
    DataComponent player_data = DATA_COMPONENT_DEFAULT;
    SpriteComponent player_sprite = {
        loadTexture("Assets/TowerDefense/TurretFullHealth.png", game.renderer), 
        (SDL_Rect){0, 0, (int)player_size.width, (int)player_size.height}
    };

    addPositionComponent(player_entity, player_position);
    addSpriteComponent(player_entity, player_sprite);
    addSizeComponent(player_entity, player_size);
    addHitboxComponent(player_entity, player_hitbox);
    addDataComponent(player_entity, player_data);
    addTag(player_entity, "Player");
    
    setDataValue(player_entity, DATA_HEALTH, 100.0f);
    setDataValue(player_entity, DATA_MAX_HEALTH, getDataValue(player_entity, DATA_HEALTH));
    setDataValue(player_entity, DATA_SPEED, 0.5f); 
    setDataValue(player_entity, DATA_ATTACK, 50.0f); 
    setDataValue(player_entity, DATA_PASSIVE, 2.0f); 
    setDataValue(player_entity, DATA_LEVEL, 1.0f);   

    // Ajout de données supplémentaires pour gérer les evenements en jeu
    setDataValue(player_entity, DATA_KILLED, 0.0f);
    setDataValue(player_entity, DATA_DIFFICULTY, 1.0f);
    setDataValue(player_entity, DATA_CAN_SHOOT, 1.0f);
    setDataValue(player_entity, DATA_COUNT_SHOOT, 0.0f);

    // Définition d'evènements supplémentaires
    bindEvent(player_entity, SDL_BUTTON_LEFT, EVENT_LEFT_MOUSECLICK, "Shoot");
    addTimerComponent(player_entity, "difficulty_increase", 30.0f, true);
    addTimerComponent(player_entity, "spawn_enemies", 15.50f, true);

    Event event_spawn_enemies;
    event_spawn_enemies.type = EVENT_TIMER_EXPIRED;
    event_spawn_enemies.data = TimerData_Init("spawn_enemies", background);
    strncpy(event_spawn_enemies.name, "spawn_enemies", sizeof(event_spawn_enemies.name) - 1);
    event_spawn_enemies.name[sizeof(event_spawn_enemies.name) - 1] = '\0';
    emitEvent(event_spawn_enemies);

    // Ajouts d'emitter de particules
    SDL_Texture* particle_texture_explosion = loadColor(game.renderer, COLOR_BLACK, 1, 1);
    SDL_Texture* particle_texture_poison = loadColor(game.renderer, COLOR_GREEN, 1, 1);
    SDL_Texture* particle_texture_trap = loadColor(game.renderer, COLOR_GRAY, 1, 1);
    SDL_Texture* particle_texture_barrel = loadColor(game.renderer, COLOR_RED, 2, 2);
    
    initParticleEmitter("Explosion", 128, particle_texture_explosion, 0, 0, 2.0f, 2.0f);
    initParticleEmitter("Poison", 128, particle_texture_poison, 0, 0, 2.0f, 2.0f);
    initParticleEmitter("Trap", 128, particle_texture_trap, 0, 0, 2.0f, 2.0f);
    initParticleEmitter("Barrel", 128, particle_texture_barrel, 0, 0, 4.0f, 4.0f);

    // Lancement du jeu
    changeState(STATE_PLAYING); 
    while (current_state != STATE_EXIT) {       
        handleState();
    }

    return 0;
}