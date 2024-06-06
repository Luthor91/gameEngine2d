#include "../include/label.h"

/**************************
    Initialisation du sprite
***************************/

Label* Label_Init(Aspect* aspect, Font* font, char* text) {  
    
    Label* label = malloc(sizeof(Label));
    if (!label) {
        return NULL;
    }

    if (aspect->scale == 0) {
        aspect->scale = 1.0;
    }

    label->aspect = aspect;
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

    SDL_RenderCopy(renderer, message, NULL, Aspect_GetScaledBounds(label->aspect));

}

void Label_RendererAspectable(Label* label, SDL_Renderer* renderer, SDL_RendererFlip flip ) {

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(label->font->ttf, label->text, *label->font->color); 
    if (!surfaceMessage) {
        printf("Label_Renderer: Erreur création surface\n");
    }

    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    if (!message) {
        printf("Label_Renderer: Erreur création texture\n");
    }

    SDL_RenderCopyEx(renderer, message, NULL, Aspect_GetScaledBounds(label->aspect), label->aspect->angle, label->aspect->center, flip);


}