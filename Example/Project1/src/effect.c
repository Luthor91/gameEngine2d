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