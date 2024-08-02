#include "../include/image.h"

Image* Image_Init(Transform* transform, Texture* texture) {

    if (!texture) {
        fprintf(stderr, "Image_Init: texture invalid, default value used\n");
        texture = Texture_Init(NULL, "Assets/Default/DefaultObject.png");
    }

    if (!transform) {
        fprintf(stderr, "Image_Init: transform invalid, default value used\n");
        transform = Transform_Init(NULL, &(Size2D){DEFAULT_IMAGE_WIDTH, DEFAULT_IMAGE_HEIGHT}, NULL, 0, 0);
    }

    Image* image = (Image*)malloc(sizeof(Image));
    if (!image) {
        fprintf(stderr, "Image_Init: Memory allocation failed for Image.\n");
        return NULL;
    }

    image->transform = transform;
    image->texture = texture;

    return image;
}

void Image_Set(Image* image, const char* params) {
    Object_Set(image, params, "Image");
}

void Image_SetPosition(Image* image, int x, int y) {

    if (x < 0) {
        x = image->transform->position->x;
    }

    if (y < 0) {
        y = image->transform->position->y;
    }
    
    image->transform->position->x = x;
    image->transform->position->y = y;

}

void Image_SetSize(Image* image, int width, int height) {

    if (width < 0) {
        width = image->transform->size->width;
    }

    if (height < 0) {
        height = image->transform->size->height;
    }
    
    image->transform->size->width = width;
    image->transform->size->height = height;

}

void Image_Destroy(Image* image) {
    SDL_DestroyTexture(image->texture->sdl_texture);
    image->texture = NULL;
}
