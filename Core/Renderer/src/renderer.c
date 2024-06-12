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

// Fonction pour ajouter plusieurs Renderers au RendererManager
void RendererManager_Add(RendererManager* manager, int num_renderers, ...) {
    va_list args;
    va_start(args, num_renderers);

    for (int i = 0; i < num_renderers; i++) {
        Renderer* renderer = va_arg(args, Renderer*);

        printf("RendererManager_Add : Adding renderer %d/%d\n", i, num_renderers-1);
        
        if (renderer == NULL) {
            fprintf(stderr, "RendererManager_Add: Renderer at index %d is NULL\n", i);
            break;
        }

        if (manager->current_renderer_count >= manager->max_renderers) {
            fprintf(stderr, "RendererManager_Add: Maximum number of renderers reached\n");
            break;
        }

        manager->renderers[manager->current_renderer_count] = renderer;
        manager->current_renderer_count++;
    }

    va_end(args);

    RendererManager_Sort(manager);
}

// Fonction pour rendre tous les Renderers dans le RendererManager
void RendererManager_Render(RendererManager* manager) {
    SDL_RenderClear(manager->sdl_renderer);

    for (int i = 0; i < manager->current_renderer_count; i++) {
        Renderer* renderer = manager->renderers[i];

        printf("RendererManager_Render: Rendering %d/%d\n", i, manager->current_renderer_count-1);
        
        // Vérification des pointeurs
        if (renderer == NULL) {
            fprintf(stderr, "RendererManager_Render: Renderer at index %d is NULL\n", i);
            continue;
        }

        if (renderer->renderFunction == NULL) {
            fprintf(stderr, "RendererManager_Render: renderFunction for renderer at index %d is NULL\n", i);
            continue;
        }

        if (manager->sdl_renderer == NULL) {
            fprintf(stderr, "RendererManager_Render: sdl_renderer for renderer at index %d is NULL\n", i);
            continue;
        }

        // Appel de la fonction de rendu
        renderer->renderFunction(renderer, manager->sdl_renderer);
        
        printf("RendererManager_Render: Success for %d/%d\n", i, manager->current_renderer_count-1);
    }

    printf("Rendering passed\n");
    SDL_RenderPresent(manager->sdl_renderer);
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

// Fonction de rendu pour les animations statiques
void Renderer_StaticAnimation(Renderer* renderer, SDL_Renderer* sdl_renderer) {
    printf("Renderer_StaticAnimation: Début de la fonction\n");

    StaticAnimation* static_animation = (StaticAnimation*)(renderer->object);
    if (!static_animation) {
        fprintf(stderr, "Renderer_StaticAnimation: static_animation est NULL\n");
        return;
    }

    printf("Renderer_StaticAnimation: static_animation n'est pas NULL\n");

    AnimationSettings* animation_settings = static_animation->animation_settings;

    printf("Renderer_StaticAnimation: animation_settings n'est pas NULL\n");
    printf("Renderer_StaticAnimation: AnimationSettings - speed: %d, current_frame: %d, max_frame: %d, last_frame_time: %d\n", 
           animation_settings->speed, animation_settings->current_frame, animation_settings->max_frame, animation_settings->start_time);

    int current_time = SDL_GetTicks();
    int elapsed_time = current_time - animation_settings->last_frame_time;

    printf("Renderer_StaticAnimation: current_time: %d, elapsed_time: %d\n", current_time, elapsed_time);

    // Si le temps écoulé est supérieur à la vitesse de l'animation, remettre à zéro
    if (elapsed_time >= animation_settings->speed) {
        elapsed_time = elapsed_time % animation_settings->speed;  // Réinitialiser le temps écoulé
        animation_settings->last_frame_time = current_time - elapsed_time;  // Mettre à jour lastUpdateTime

        // Passer à la frame suivante
        animation_settings->current_frame++;
        if (animation_settings->current_frame >= animation_settings->max_frame) {
            animation_settings->current_frame = 0; // Recommencer l'animation
        }

        printf("Renderer_StaticAnimation: Frame changée - current_frame: %d, last_frame_time: %d\n", 
               animation_settings->current_frame, animation_settings->last_frame_time);
    }

    // Progression proportionnelle à l'animation
    float progress = (float)elapsed_time / animation_settings->speed;
    printf("Renderer_StaticAnimation: progress: %f\n", progress);

    // Obtenir les frames de départ et de fin
    AnimationFrame* start_frame = static_animation->frames[animation_settings->current_frame];
    AnimationFrame* end_frame = static_animation->frames[(animation_settings->current_frame + 1) % animation_settings->max_frame];

    if (!start_frame || !end_frame) {
        fprintf(stderr, "Renderer_StaticAnimation: start_frame ou end_frame est NULL\n");
        return;
    }

    printf("Renderer_StaticAnimation: start_frame ID: %d, end_frame ID: %d\n", start_frame->id, end_frame->id);

    // Calcul des positions et tailles interpolées
    SDL_Rect interpolated_position;

    // Interpolation des positions
    interpolated_position.x = start_frame->transform->position->x + (int)((end_frame->transform->position->x - start_frame->transform->position->x) * progress);
    interpolated_position.y = start_frame->transform->position->y + (int)((end_frame->transform->position->y - start_frame->transform->position->y) * progress);

    printf("Renderer_StaticAnimation: interpolated_position - x: %d, y: %d\n", 
           interpolated_position.x, interpolated_position.y);

    // Interpolation des tailles
    interpolated_position.w = start_frame->transform->size->width + (int)((end_frame->transform->size->width - start_frame->transform->size->width) * progress);
    interpolated_position.h = start_frame->transform->size->height + (int)((end_frame->transform->size->height - start_frame->transform->size->height) * progress);

    printf("Renderer_StaticAnimation: interpolated_position - w: %d, h: %d\n", 
           interpolated_position.w, interpolated_position.h);

    // Rendre la frame actuelle
    if (SDL_RenderCopy(sdl_renderer, start_frame->texture->sdl_texture, NULL, &interpolated_position) != 0) {
        fprintf(stderr, "Renderer_StaticAnimation: SDL_RenderCopy error: %s\n", SDL_GetError());
    } else {
        printf("Renderer_StaticAnimation: SDL_RenderCopy successful\n");
    }

    printf("Renderer_StaticAnimation: Fin de la fonction\n");
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

// Définition de la fonction Renderer_Tilemap ici
void Renderer_Tilemap(Renderer* renderer, SDL_Renderer* sdl_renderer) {
    Tilemap* tilemap = (Tilemap*)(renderer->object);

    // Parcourir toutes les lignes et colonnes du tilemap
    for (int row = 0; row < tilemap->rows; row++) {
        for (int col = 0; col < tilemap->columns; col++) {
            int tile_id = tilemap->map[row * tilemap->columns + col];
            Tile* tile = tilemap->tiles[tile_id];

            // Définir la position et la taille de la tuile à dessiner
            SDL_Rect dst_rect;
            dst_rect.x = col * tilemap->tile_size.width;
            dst_rect.y = row * tilemap->tile_size.height;
            dst_rect.w = tilemap->tile_size.width;
            dst_rect.h = tilemap->tile_size.height;

            // Définir la source de la texture (dans le cas d'une texture avec des sous-régions)
            SDL_Rect src_rect;
            src_rect.x = tile->position->x;
            src_rect.y = tile->position->y;
            src_rect.w = tile->size.width;
            src_rect.h = tile->size.height;

            // Dessiner la texture de la tuile à l'écran
            SDL_RenderCopy(sdl_renderer, tile->texture->sdl_texture, &src_rect, &dst_rect);
        }
    }
}

void Renderer_DynamicAnimationManager(Renderer* renderer, SDL_Renderer* sdl_renderer) {
    DynamicAnimationManager* manager = (DynamicAnimationManager*)(renderer->object);
    for (int i = 0; i < manager->index; ++i) {
        printf("Renderer_DynamicAnimationManager : rendering %d/%d\n", i, manager->index-1);
        Renderer_DynamicAnimation(renderer, sdl_renderer);
    }
}

void Renderer_StaticAnimationManager(Renderer* renderer, SDL_Renderer* sdl_renderer) {
    StaticAnimationManager* manager = (StaticAnimationManager*)(renderer->object);
    for (int i = 0; i < manager->index; ++i) {
        printf("Renderer_StaticAnimationManager : rendering %d/%d\n", i, manager->index-1);
        Renderer_StaticAnimation(renderer, sdl_renderer);
    }
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