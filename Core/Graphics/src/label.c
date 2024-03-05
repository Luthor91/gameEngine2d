#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../include/label.h"

/**************************
    Fichier source décrivant les fonctions associé au Label : 

    typedef struct Label {
        SDL_Renderer* renderer;
        SDL_Surface* texture;
        Transform* transform;
        SDL_Color* color;
        TTF_Font* font;
        int font_size;
        char* text;
    } Label;

***************************/


/**************************
    Initialisation du sprite
***************************/

Label* Label_Init(Transform* transform, SDL_Color* color_font, const char* font, char* text, int size_font) {  
    
    Label* label = malloc(sizeof(Label));
    if (!label) {
        return NULL;
    }

    if(!TTF_WasInit() && TTF_Init() == -1) {
        printf("Label_Init: %s\n", TTF_GetError());
        free(label);
        return NULL;
    }

    TTF_Font* ttf_font = TTF_OpenFont(font, size_font);
    if (!ttf_font) {
        printf("Label_Init: %s\n", TTF_GetError());
        TTF_CloseFont(ttf_font);
        free(label);
        return NULL;
    }

    if (transform->scale == 0) {
        transform->scale = 1.0;
    }

    label->transform = transform;
    label->color = color_font;
    label->font = ttf_font;
    label->text = text;

    return label;
}

void Label_Renderer(Label* label, SDL_Renderer* renderer) {

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(label->font, label->text, *label->color); 
    if (!surfaceMessage) {
        printf("Label_Renderer: Erreur création surface\n");
    }

    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    if (!message) {
        printf("Label_Renderer: Erreur création texture\n");
    }

    SDL_RenderCopy(renderer, message, NULL, Transform_GetScaledBounds(label->transform));

}