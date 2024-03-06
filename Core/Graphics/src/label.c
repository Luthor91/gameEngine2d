#include "../include/label.h"

/**************************
    Initialisation du sprite
***************************/

Label* Label_Init(Transform* transform, Font* font, char* text) {  
    
    Label* label = malloc(sizeof(Label));
    if (!label) {
        return NULL;
    }

    if (transform->scale == 0) {
        transform->scale = 1.0;
    }

    label->transform = transform;
    label->font = font;
    label->text = text;

    return label;
}

void Label_RendererStatic(Label* label, SDL_Renderer* renderer) {

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(label->font->ttf, label->text, *label->font->color); 
    if (!surfaceMessage) {
        printf("Label_Renderer: Erreur création surface\n");
    }

    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    if (!message) {
        printf("Label_Renderer: Erreur création texture\n");
    }

    SDL_RenderCopy(renderer, message, NULL, Transform_GetScaledBounds(label->transform));

}

void Label_RendererTransformable(Label* label, SDL_Renderer* renderer, SDL_RendererFlip flip ) {

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(label->font->ttf, label->text, *label->font->color); 
    if (!surfaceMessage) {
        printf("Label_Renderer: Erreur création surface\n");
    }

    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    if (!message) {
        printf("Label_Renderer: Erreur création texture\n");
    }

    SDL_RenderCopyEx(renderer, message, NULL, Transform_GetScaledBounds(label->transform), label->transform->angle, label->transform->center, flip);


}