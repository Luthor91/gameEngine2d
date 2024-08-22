#include "../../Core/core.h"
#include "src/global.h"

int main(int argc, char* argv[]) {
    Init_All();

    EventType EVENT_LEFT_MOUSECLICK = getEventType("EVENT_LEFT_MOUSECLICK");
    EventType EVENT_LEVEL_UP = getEventType("EVENT_LEVEL_UP");
    EventType EVENT_DEATH = getEventType("EVENT_DEATH");
    EventType EVENT_INFO = getEventType("EVENT_INFO");
    EventType EVENT_COLLIDE = getEventType("EVENT_COLLIDE");
    EventType EVENT_TIMER_EXPIRED = getEventType("EVENT_TIMER_EXPIRED");

    // Ajouter des listeners pour les événements
    addEventListener(EVENT_LEFT_MOUSECLICK, onBullet_Shoot);
    addEventListener(EVENT_LEVEL_UP, onLeveling_Up);
    addEventListener(EVENT_DEATH, onDeath);
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
    int DATA_CAPABLE = addDataType("DATA_CAPABLE");
    int DATA_COUNT_SHOOT = addDataType("DATA_COUNT_SHOOT");
    int DATA_ACCUMULATION = addDataType("DATA_ACCUMULATION");
     
    // Définition du fond d'écran
    Entity background = createEntity();
    PositionComponent background_position = POSITION_ZERO;
    addPositionComponent(background, background_position);
    SpriteComponent background_sprite = {
        loadTexture("Assets/TowerDefense/BackgroundSpace.png", g_renderer), 
        (SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}
    };
    addSpriteComponent(background, background_sprite);

    // Définition du player
    player_entity = createEntity();
    PositionComponent player_position = {WINDOW_WIDTH/2 - 16, WINDOW_HEIGHT/2};
    SizeComponent player_size = {32, 32};
    HitboxComponent player_hitbox = { 0, 0, player_size.width, player_size.height, true};
    DataComponent player_data = DATA_COMPONENT_DEFAULT;
    SDL_Texture* player_texture = loadTexture("Assets/TowerDefense/TurretFullHealth.png", g_renderer);
    addPositionComponent(player_entity, player_position);
    SpriteComponent player_sprite = {
        player_texture, 
        (SDL_Rect){0, 0, (int)player_size.width, (int)player_size.height}
    };
    addSpriteComponent(player_entity, player_sprite);
    addSizeComponent(player_entity, player_size);
    addHitboxComponent(player_entity, player_hitbox);
    addDataComponent(player_entity, player_data);
    addTag(player_entity, "Player");
    setDataValue(player_entity, DATA_HEALTH, 100.0f);
    setDataValue(player_entity, DATA_MAX_HEALTH, getDataValue(player_entity, DATA_HEALTH));
    setDataValue(player_entity, DATA_SPEED, 2.0f); 
    setDataValue(player_entity, DATA_ATTACK, 35.0f); 
    setDataValue(player_entity, DATA_PASSIVE, 2.0f); 
    setDataValue(player_entity, DATA_LEVEL, 1.0f);   

    // Ajout de données supplémentaires pour gérer les evenements en jeu
    setDataValue(player_entity, DATA_KILLED, 0.0f); // enemies_killed
    setDataValue(player_entity, DATA_DIFFICULTY, 1.0f);
    setDataValue(player_entity, DATA_CAPABLE, 1.0f); // can_shoot
    setDataValue(player_entity, DATA_COUNT_SHOOT, 0.0f);

    // Définition d'evènements supplémentaires
    bindEvent(player_entity, SDL_BUTTON_LEFT, EVENT_LEFT_MOUSECLICK, "Shoot");
    addTimerComponent(player_entity, "difficulty_increase", 30.0f, true);
    addTimerComponent(player_entity, "spawn_enemies", 20.0f, true);
    emitEvent((Event)
        {
            EVENT_TIMER_EXPIRED, 
            TimerData_Init("spawn_enemies", background)
        }
    );

    // Ajouts d'emitter de particules
    SDL_Texture* particle_texture_explosion = loadColor(g_renderer, COLOR_RED, 1, 1);
    SDL_Texture* particle_texture_poison = loadColor(g_renderer, COLOR_GREEN, 1, 1);
    SDL_Texture* particle_texture_trap = loadColor(g_renderer, COLOR_BLACK, 1, 1);
    
    initParticleEmitter("Explosion", 64, particle_texture_explosion, 0, 0, 2.0f, 2.0f);
    initParticleEmitter("Poison", 64, particle_texture_poison, 0, 0, 2.0f, 2.0f);
    initParticleEmitter("Trap", 64, particle_texture_trap, 0, 0, 2.0f, 2.0f);

    // Lancement du jeu
    changeState(STATE_PLAYING);
    while (current_state != STATE_EXIT) {
        handleState();
    }

    return 0;
}