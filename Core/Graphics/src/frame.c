#include "../include/frame.h"

/**************************
    Initialisation du sprite
***************************/
Frame* Frame_Init(SDL_Rect* bounds, SDL_Texture* texture, int id) {

    if (!texture) {
        printf("Frame_Init: texture inexistant\n");
        return;
    }
    if (!bounds) {
        printf("Frame_Init: bounds inexistant\n");
        return;
    }  
    
    Frame* frame = malloc(sizeof(Frame));
    if (!frame) {
        printf("Frame_Init: frame inexistant\n");
        return;
    } 

    bounds->x = 0;
    bounds->y = 0;
    frame->texture = texture;
    frame->bounds = bounds;
    frame->id = id;

    return frame;

}

void Frame_SetBounds(Frame* frame, SDL_Rect* origin) {

    if (!frame) {
        printf("Frame_SetBounds: frame inexistant\n");
        return;
    }
    if (!origin) {
        printf("Frame_SetBounds: origin inexistant\n");
        return;
    }  
    frame->origin = origin;

    return;

}

void Frame_Render(Frame* frame, SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, frame->texture, frame->bounds, frame->origin);
}