#include "../include/frame.h"

/**************************
    Initialisation du sprite
***************************/
Frame* Frame_Init(SDL_Rect* origin, SDL_Rect* target, SDL_Texture* texture, float delay, int id) {

    if (!texture) {
        printf("Frame_Init: texture inexistant\n");
        return NULL;
    }
    if (!origin) {
        printf("Frame_Init: origin inexistant\n");
        return NULL;
    }  
    if (!target) {
        printf("Frame_Init: target inexistant\n");
        return NULL;
    }  
    
    Frame* frame = malloc(sizeof(Frame));
    if (!frame) {
        printf("Frame_Init: frame inexistant\n");
        return NULL;
    } 

    frame->texture = texture;
    frame->origin = origin;
    frame->target = target;
    frame->delay = delay;
    frame->id = id;

    return frame;

}

void Frame_SetOrigin(Frame* frame, SDL_Rect* origin) {

    if (!frame) {
        printf("Frame_SetOrigin: frame inexistant\n");
        return;
    }
    if (!origin) {
        printf("Frame_SetOrigin: origin inexistant\n");
        return;
    }  
    frame->origin = origin;

    return;

}

void Frame_Render(Frame* frame, SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, frame->texture, frame->origin, frame->origin);
}

void Frame_Render_Debug(Frame* frame, SDL_Renderer* renderer) {
    int texW = 0, texH = 0;
    SDL_QueryTexture(frame->texture, NULL, NULL, &texW, &texH);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, frame->target);
}