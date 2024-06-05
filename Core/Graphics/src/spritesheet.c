#include "../include/spritesheet.h"

SpriteSheet* SpriteSheet_Init(SDL_Renderer* renderer, Sprite* sprite, int tile_width, int tile_height, int max_frame) {
    if (!sprite || !sprite->texture) {
        printf("SpriteSheet_Init: Erreur lors de la création de la texture\n");
        return NULL;
    }

    int num_cols = sprite->transform->bounds->w / tile_width;
    int num_rows = sprite->transform->bounds->h / tile_height;

    SpriteSheet* spritesheet = (SpriteSheet*)malloc(sizeof(SpriteSheet));
    if (!spritesheet) {
        printf("SpriteSheet_Init: Erreur lors de l'allocation de mémoire pour l'animation\n");
        SDL_DestroyTexture(sprite->texture);
        return NULL;
    }

    spritesheet->max_frame = max_frame;

    Frame** frames = (Frame**)malloc(num_cols * num_rows * sizeof(Frame*));
    int frame_index = 0;

    for (int y = 0; y < num_rows; y++) {
        for (int x = 0; x < num_cols; x++) {
            if (frame_index >= max_frame) {
                break;
            }

            SDL_Rect origin = { x * tile_width, y * tile_height, tile_width, tile_height };
            SDL_Rect target = { 0, 0, tile_width, tile_height };

            SDL_Texture* frame_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, tile_width, tile_height);
            if (!frame_texture) {
                fprintf(stderr, "AnimationSpriteSheet_Init: Erreur création sous-texture:\n\t %s\n", SDL_GetError());
                return NULL;
            }
            Frame* frame = Frame_Init(&origin, &target, frame_texture, frame_index, frame_index);

            SDL_SetTextureBlendMode(frame_texture, SDL_BLENDMODE_NONE);
            SDL_SetRenderTarget(renderer, frame_texture);
            SDL_RenderCopy(renderer, sprite->texture, &origin, NULL);
            SDL_SetRenderTarget(renderer, NULL);
            SDL_SetTextureBlendMode(frame_texture, SDL_BLENDMODE_BLEND);

            frames[frame_index] = frame;
            frame_index++;
        }
    }

    spritesheet->frames = frames;

    return spritesheet;
}