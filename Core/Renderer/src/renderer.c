#include "../include/renderer.h"

// Fonction d'initialisation du RendererManager
RendererManager* RendererManager_Init(SDL_Renderer* sdl_renderer, int max_renderers) {
    RendererManager* manager = (RendererManager*)malloc(sizeof(RendererManager));
    if (!manager) {
        fprintf(stderr, "RendererManager_Init: Memory allocation failed\n");
        return NULL;
    }

    manager->sdl_renderer = sdl_renderer;
    manager->max_renderers = max_renderers;
    manager->current_renderer_count = 0;

    manager->renderers = (Renderer**)malloc(sizeof(Renderer*) * max_renderers);
    if (!manager->renderers) {
        fprintf(stderr, "RendererManager_Init: Memory allocation for renderers failed\n");
        free(manager);
        return NULL;
    }

    return manager;
}

// Fonction d'initialisation d'un Renderer
Renderer* Renderer_Init(void* renderFunction, void* object, int z_index) {
    Renderer* renderer = (Renderer*)malloc(sizeof(Renderer));
    if (!renderer) {
        fprintf(stderr, "Renderer_Init: Memory allocation failed\n");
        return NULL;
    }

    renderer->renderFunction = renderFunction;
    renderer->object = object;
    renderer->z_index = z_index;

    return renderer;
}

// Fonction pour ajouter un Renderer au RendererManager
void RendererManager_Add(RendererManager* manager, Renderer* renderer) {
    if (manager->current_renderer_count >= manager->max_renderers) {
        fprintf(stderr, "RendererManager_Add: Maximum number of renderers reached\n");
        return;
    }

    manager->renderers[manager->current_renderer_count] = renderer;
    manager->current_renderer_count++;
    RendererManager_Sort(manager);
}

// Fonction pour rendre tous les Renderers dans le RendererManager
void RendererManager_Render(RendererManager* manager) {
    for (int i = 0; i < manager->current_renderer_count; i++) {
        Renderer* renderer = manager->renderers[i];
        renderer->renderFunction(renderer, manager->sdl_renderer);
    }
}

void Renderer_DynamicAnimation(Renderer* renderer, SDL_Renderer* sdl_renderer) {
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
    SDL_RenderCopy(sdl_renderer, curr_frame->texture->sdl_texture, NULL, &interpolated_position);
}

void Renderer_StaticAnimation(Renderer* renderer, SDL_Renderer* sdl_renderer) {
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
    SDL_RenderCopy(sdl_renderer, start_frame->texture->sdl_texture, NULL, &interpolated_position);
}

void Renderer_Sprite(Renderer* renderer, SDL_Renderer* sdl_renderer) {
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

    SDL_RenderCopyEx(sdl_renderer, sprite->texture->sdl_texture, NULL, &target, sprite->transform->angle, (const SDL_Point*)sprite->transform->center, sprite->transform->flip);

}

void Renderer_Label(Renderer* renderer, SDL_Renderer* sdl_renderer) {

    Label* label = (Label*)(renderer->object);

    SDL_Color color = Color_GetSDL(*label->font->color);

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(label->font->ttf, label->text, color); 
    if (!surfaceMessage) {
        printf("Label_Renderer: Erreur création surface\n");
    }

    SDL_Texture* message = SDL_CreateTextureFromSurface(sdl_renderer, surfaceMessage);
    if (!message) {
        printf("Label_Renderer: Erreur création texture\n");
    }

    SDL_Rect target;
    target.x = label->transform->position->x;
    target.y = label->transform->position->y;
    target.w = label->transform->size->width;
    target.h = label->transform->size->height;

    SDL_RenderCopyEx(sdl_renderer, message, NULL, &target, label->transform->angle, (const SDL_Point*)label->transform->center, label->transform->flip);

}

void Renderer_Window(Renderer* renderer, SDL_Renderer* sdl_renderer) {

    Window* window = (Window*)(renderer->object);

    // Définir la position et la taille de la texture à dessiner
    SDL_Rect dst_rect;
    dst_rect.x = (int)window->transform->position->x;
    dst_rect.y = (int)window->transform->position->y;
    dst_rect.w = (int)(window->transform->size->width * window->transform->scale);
    dst_rect.h = (int)(window->transform->size->height * window->transform->scale);

    // Dessine la texture à l'écran
    SDL_RenderCopy(window->renderer, window->texture->sdl_texture, NULL, &dst_rect);

}

// Fonction de tri des Renderers par z_index (ordre croissant)
void RendererManager_Sort(RendererManager* manager) {
    for (int i = 0; i < manager->current_renderer_count - 1; i++) {
        for (int j = 0; j < manager->current_renderer_count - i - 1; j++) {
            if (manager->renderers[j]->z_index > manager->renderers[j + 1]->z_index) {
                Renderer* temp = manager->renderers[j];
                manager->renderers[j] = manager->renderers[j + 1];
                manager->renderers[j + 1] = temp;
            }
        }
    }
}