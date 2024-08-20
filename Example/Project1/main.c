#include "../../Core/core.h"
#include "src/global.h"

int main(int argc, char* argv[]) {
    Init_All();

    // Ajouter des listeners pour les événements
    addEventListener(EVENT_TYPE_LEFT_MOUSECLICK, onClick);
    addEventListener(EVENT_TYPE_COLLIDE, onBullet_CollideWith_Enemy);
    addEventListener(EVENT_TYPE_COLLIDE, onEnemy_CollideWith_Player);
    addEventListener(EVENT_TYPE_COLLIDE, onTrap_CollideWith_Enemy);
    addEventListener(EVENT_TYPE_COLLIDE, onBullet_CollideWith_Barrel);
    
    addEventListener(EVENT_TYPE_DEATH, onDeath);
    addEventListener(EVENT_TYPE_TIMER_EXPIRED, uponReloading);
    addEventListener(EVENT_TYPE_TIMER_EXPIRED, uponInvincibilityFinished);
    addEventListener(EVENT_TYPE_TIMER_EXPIRED, uponIncreasingDifficulty);
    addEventListener(EVENT_TYPE_TIMER_EXPIRED, uponSpawningEnemies);
    addEventListener(EVENT_TYPE_TIMER_EXPIRED, uponDispawningTrap);
    addEventListener(EVENT_TYPE_TIMER_EXPIRED, uponSpawnBarrel);
    addEventListener(EVENT_TYPE_TIMER_EXPIRED, uponDispawnBarrel);
    addEventListener(EVENT_TYPE_LEVEL_UP, onLeveling_Up);
     
    // Définition du fond d'écran
    Entity background = createEntity();
    PositionComponent backgroundPosition = POSITION_ZERO;
    addPositionComponent(background, backgroundPosition);
    SpriteComponent backgroundSprite = {
        loadTexture("Assets/Default/DefaultBackground_Space.png", g_renderer), 
        (SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}
    };
    addSpriteComponent(background, backgroundSprite);

    // Définition du player
    playerEntity = createEntity();
    PositionComponent playerPosition = {WINDOW_WIDTH/2 - 16, WINDOW_HEIGHT/2};
    SizeComponent playerSize = {32, 32};
    HitboxComponent playerHitbox = { 0, 0, playerSize.width, playerSize.height, true};
    DataComponent playerData = DATA_COMPONENT_DEFAULT;
    SDL_Texture* playerTexture = loadTexture("Assets/Default/DefaultTurret.png", g_renderer);
    addPositionComponent(playerEntity, playerPosition);
    SpriteComponent playerSprite = {
        playerTexture, 
        (SDL_Rect){0, 0, 32, 32}
    };
    addSpriteComponent(playerEntity, playerSprite);
    addSizeComponent(playerEntity, playerSize);
    addHitboxComponent(playerEntity, playerHitbox);
    addDataComponent(playerEntity, playerData);
    addTag(playerEntity, "Player");
    setDataValue(playerEntity, DATA_HEALTH, 100.0f);
    setDataValue(playerEntity, DATA_SPEED, 0.5f); 
    setDataValue(playerEntity, DATA_ATTACK, 35.0f); 
    setDataValue(playerEntity, DATA_PASSIVE, 2.0f); 
    setDataValue(playerEntity, DATA_LEVEL, 1.0f); 

    bindEvent(playerEntity, SDL_BUTTON_LEFT, EVENT_TYPE_LEFT_MOUSECLICK, "Shoot");
    addTimerComponent(playerEntity, "difficulty_increase", 30.0f, true);
    addTimerComponent(playerEntity, "spawn_enemies", 20.0f, true);
    emitEvent((Event)
        {
            EVENT_TYPE_TIMER_EXPIRED, 
            TimerData_Init("spawn_enemies", background)
        }
    );
    // enemies_killed
    setDataValue(playerEntity, DATA_SCORE, 0.0f);
    // Difficulty
    setDataValue(playerEntity, DATA_DIFFICULTY, 1.0f);
    // can_shoot
    setDataValue(playerEntity, DATA_CAPABLE, 1.0f);
    // bullet_count
    setDataValue(playerEntity, DATA_COUNT_SHOOT, 0.0f);

    SDL_Texture* particleTexture = loadColor(g_renderer, COLOR_RED, 1, 1);
    initParticleEmitter("Explosion", 24, particleTexture, 0, 0, 1.5f, 2.0f);
    addTimerComponent(playerEntity, "spawn_barrel", 1.0f, true);
     
    changeState(STATE_PLAYING);
    while (currentState != STATE_EXIT) {
        handleState();
    }

    return 0;
}