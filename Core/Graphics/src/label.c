#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../include/label.h"

/**************************
    Fichier source décrivant les fonctions associé au Label : 

    typedef struct Label {
        SDL_Renderer* renderer;
        SDL_Surface* surface;
        SDL_Color color;
        SDL_Rect rect;
        SDL_Point center;
        TTF_Font* font;
        char* text;
        //SDL_Texture texture;
        double angle;
        double scale;
    } Label;


***************************/


/**************************
    Initialisation du sprite
***************************/

Label* Label_Init(SDL_Renderer* renderer, SDL_Rect* rect, SDL_Point* center, SDL_Color* color_font, char* font, char* text, int size_font, double scale, double angle) {  
    
    if(!TTF_WasInit() && TTF_Init() == -1) {
        printf("Label_Init: %s\n", TTF_GetError());
        return NULL;
    }

    Label* label;

    TTF_Font* ttf_font = TTF_OpenFont(font, size_font);
    if (!ttf_font) {
        printf("Label_Init: %s\n", TTF_GetError());
        TTF_CloseFont(ttf_font);
        return NULL;
    }

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(ttf_font, text, *color_font);
    if (!surfaceMessage) {
        printf("Label_Init: Erreur création surface\n");
        return NULL;
    }

    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    if (!message) {
        printf("Label_Init: Erreur création texture\n");
        return NULL;
    }

    label->rect = rect;
    label->color = color_font;
    label->font = ttf_font;
    label->text = text;

    return label;
}

void Label_SetFont(Label* label, char* font, int size_font) {

    if(size_font <= 1) {
        size_font = 1;
    }

    label->font = TTF_OpenFont(font, size_font);

}

void Label_SetColor(Label* label, SDL_Color* color_font) {

    label->color = color_font;

}

void Label_SetMessage(Label* label, char* message) {

    label->text = message;

}

void Label_SetRect(Label* label) {

    int new_w = (int)(label->rect->w * label->scale);
    int new_h = (int)(label->rect->h * label->scale);

    if (new_w >= 1) {
        label->rect->w = (int)new_w;
    }
    if (new_h >= 1) {
        label->rect->h = (int)new_h;
    }

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

    SDL_RenderCopy(renderer, message, NULL, label->rect);

}