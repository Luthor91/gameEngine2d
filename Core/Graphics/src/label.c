#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../include/label.h"

/**************************
    Fichier source décrivant les fonctions associé au Sprite : 

***************************/


/**************************
    Initialisation du sprite
***************************/

Label* Label_Init(SDL_Renderer* renderer, SDL_Rect rect, SDL_Point center, SDL_Color color_font, char* font, char* text, int size_font, double scale, double angle) {  
    
    Label* label;
    TTF_Font* ttf_font = TTF_OpenFont(font, size_font);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(ttf_font, text, color_font); 
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    label->rect = rect;
    label->color = &color_font;
    //label->texture = message;
    
    SDL_RenderCopy(renderer, message, NULL, &label->rect);


    return label;
}
