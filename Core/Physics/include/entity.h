// entity.h

#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include "sprite.h"
#include "animated_sprite.h"
#include "animated_spritesheet.h"

typedef enum {
    SPRITE,
    ANIMATED_SPRITE,
    ANIMATED_SPRITESHEET
} SpriteType;

typedef struct {
    SpriteType type;
    Transform* transform;
    union {
        Sprite* sprite;
        AnimatedSprite* animatedSprite;
        AnimatedSpriteSheet* animatedSpriteSheet;
    } data;
} Entity;

Entity* Entity_Init(SpriteType type, Transform* transform);
void Entity_Destroy(Entity* entity);

#endif // ENTITY_H
