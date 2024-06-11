#include "../../Animation/include/dynamic_animation.h"
#include "../../Animation/include/static_animation.h"
#include "../../Animation/include/animation_settings.h"
#include "../../Graphics/include/sprite.h"
#include "../../Spatial/include/point2d.h"
#include "../../Spatial/include/size2d.h"
#include "../../Font/include/label.h"
#include "../include/renderer.h"

// Fonction d'initialisation pour la structure Renderer
Renderer* Renderer_Init(void* renderFunction, void* object, SDL_Renderer* sdl_renderer) {
    // Allocation de mémoire pour la structure Renderer
    Renderer* renderer = (Renderer*)malloc(sizeof(Renderer));
    if (renderer == NULL) {
        return NULL; // Retourner NULL en cas d'échec de l'allocation
    }

    // Initialisation des membres de la structure
    renderer->renderFunction = renderFunction;
    renderer->object = object;
    renderer->sdl_renderer = sdl_renderer;

    return renderer;
}

void Renderer_DynamicAnimation(Renderer* renderer) {
    DynamicAnimation* dynamic_animation = (DynamicAnimation*)(renderer->object);
    AnimationSettings* animation_settings = dynamic_animation->animation_settings;

    int current_time = SDL_GetTicks();
    int elapsed_time = current_time - animation_settings->last_frame_time;

    // Gestion du timing des frames
    if (elapsed_time >= animation_settings->speed) {
        animation_settings->current_frame++;
        animation_settings->last_frame_time = current_time;

        if (animation_settings->current_frame >= animation_settings->max_frame) {
            animation_settings->current_frame = 0;
        }
    }

    // Calcul de la progression totale de l'animation
    float overall_progress = (float)elapsed_time / animation_settings->speed;

    SDL_Rect interpolated_position;

    if (overall_progress > 1.0f) {
        if (animation_settings->repeat == 0) {
            overall_progress = 1.0f;
        } else {
            overall_progress = 0.0f;
            animation_settings->start_time = SDL_GetTicks();

            // Initialiser la position interpolée aux valeurs de départ
            AnimationFrame* start_frame = dynamic_animation->startFrames[animation_settings->current_frame];
            interpolated_position.x = start_frame->transform->position->x;
            interpolated_position.y = start_frame->transform->position->y;
            interpolated_position.w = start_frame->transform->size->width;
            interpolated_position.h = start_frame->transform->size->height;
        }
    }

    // Obtenir les frames courantes et suivantes
    AnimationFrame* curr_frame = dynamic_animation->startFrames[animation_settings->current_frame];
    AnimationFrame* next_frame = dynamic_animation->startFrames[(animation_settings->current_frame + 1) % animation_settings->max_frame];

    // Calcul des positions et tailles interpolées
    Point2D* start_position = curr_frame->transform->position;
    Point2D* end_position = dynamic_animation->endFrames[animation_settings->current_frame]->transform->position;
    Size2D* start_size = curr_frame->transform->size;
    Size2D* end_size = dynamic_animation->endFrames[animation_settings->current_frame]->transform->size;

    // Interpolation des positions
    interpolated_position.x = start_position->x + (int)((end_position->x - start_position->x) * overall_progress);
    interpolated_position.y = start_position->y + (int)((end_position->y - start_position->y) * overall_progress);

    // Interpolation des tailles
    interpolated_position.w = start_size->width + (int)((end_size->width - start_size->width) * overall_progress);
    interpolated_position.h = start_size->height + (int)((end_size->height - start_size->height) * overall_progress);

    // Rendu de la texture interpolée
    SDL_RenderCopy(renderer->sdl_renderer, curr_frame->texture->sdl_texture, NULL, &interpolated_position);
}

void Render_StaticAnimation(Renderer* renderer) {
    StaticAnimation* static_animation = (StaticAnimation*)(renderer->object);
    AnimationSettings* animation_settings = static_animation->animation_settings;

    int current_time = SDL_GetTicks();
    int elapsed_time = current_time - animation_settings->last_frame_time;

    // Si le temps écoulé est supérieur à la vitesse de l'animation, remettre à zéro
    if (elapsed_time >= animation_settings->speed) {
        elapsed_time = elapsed_time % animation_settings->speed;  // Réinitialiser le temps écoulé
        animation_settings->last_frame_time = current_time - elapsed_time;  // Mettre à jour lastUpdateTime

        // Passer à la frame suivante
        animation_settings->current_frame++;
        if (animation_settings->current_frame >= animation_settings->max_frame) {
            animation_settings->current_frame = 0; // Recommencer l'animation
        }
    }

    // Progression proportionnelle à l'animation
    float progress = (float)elapsed_time / animation_settings->speed;

    // Obtenir les frames de départ et de fin
    AnimationFrame* start_frame = static_animation->frames[animation_settings->current_frame];
    AnimationFrame* end_frame = static_animation->frames[(animation_settings->current_frame + 1) % animation_settings->max_frame];

    // Calcul des positions et tailles interpolées
    SDL_Rect interpolated_position;

    // Interpolation des positions
    interpolated_position.x = start_frame->transform->position->x + (int)((end_frame->transform->position->x - start_frame->transform->position->x) * progress);
    interpolated_position.y = start_frame->transform->position->y + (int)((end_frame->transform->position->y - start_frame->transform->position->y) * progress);

    // Interpolation des tailles
    interpolated_position.w = start_frame->transform->size->width + (int)((end_frame->transform->size->width - start_frame->transform->size->width) * progress);
    interpolated_position.h = start_frame->transform->size->height + (int)((end_frame->transform->size->height - start_frame->transform->size->height) * progress);

    // Render the current frame
    SDL_RenderCopy(renderer->sdl_renderer, start_frame->texture->sdl_texture, NULL, &interpolated_position);
}

void Render_Sprite(Renderer* renderer) {
    Sprite* sprite = (Sprite*)(renderer->object);

    if (!renderer || !sprite->texture){
        printf("Sprite_RenderStatic: Erreur pendant l'affichage\n\t%s\n", SDL_GetError());
        return;
    }

    // Calcul des positions et tailles interpolées
    SDL_Rect target;
    target.x = sprite->transform->position->x;
    target.y = sprite->transform->position->y;
    target.w = sprite->transform->size->width;
    target.h = sprite->transform->size->height;

    SDL_RenderCopyEx(renderer->sdl_renderer, sprite->texture, NULL, &target, sprite->transform->angle, sprite->transform->center, sprite->transform->flip);

}

void Render_Label(Renderer* renderer) {

    Label* label = (Label*)(renderer->object);

    SDL_Color color = Color_GetSDL(*label->font->color);

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(label->font->ttf, label->text, color); 
    if (!surfaceMessage) {
        printf("Label_Renderer: Erreur création surface\n");
    }

    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    if (!message) {
        printf("Label_Renderer: Erreur création texture\n");
    }

    SDL_Rect target;
    target.x = label->transform->position->x;
    target.y = label->transform->position->y;
    target.w = label->transform->size->width;
    target.h = label->transform->size->height;

    SDL_RenderCopyEx(renderer, message, NULL, &target, label->transform->angle, label->transform->center, label->transform->flip);

}