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
}

// Fonction pour fusionner les textures des sprites ayant le même axe_z
void RendererManager_Flatten(RendererManager* manager) {
    // Vérifiez si le manager et son tableau de renderers sont valides
    if (!manager || !manager->renderers) {
        printf("RendererManager_Flatten: Erreur - manager ou manager->renderers est NULL\n");
        return;
    }

    // Assurez-vous que le premier renderer est la fenêtre
    Window* window = manager->renderers[0]->object;
    if (!window) {
        printf("RendererManager_Flatten: Erreur - le renderer de la fenêtre est NULL\n");
        return;
    }

    int window_width = window->texture->size->width;
    int window_height = window->texture->size->height;
    printf("window_width: %d, window_height: %d\n", window_width, window_height);

    // Utilisation d'un dictionnaire pour regrouper les renderers par axe_z
    typedef struct ZGroup {
        int z_index;
        SDL_Texture* merged_texture;
    } ZGroup;

    size_t z_count = 0;
    ZGroup z_groups[4096];
    memset(z_groups, 0, sizeof(z_groups));

    // Parcourez chaque renderer dans le tableau
    for (size_t i = 1; i < manager->current_renderer_count - 1; i++) {
        Renderer* renderer = manager->renderers[i];
        printf("Renderer %zu: renderer = %p\n", i, (void*)renderer);

        // Vérifiez si le renderer et son objet sont valides
        if (!renderer || !renderer->object) {
            printf("RendererManager_Flatten: Renderer ou renderer->object est NULL à l'indice %zu\n", i);
            continue;
        }

        // Vérification si l'objet est un Sprite
        Sprite* sprite = (Sprite*)renderer->object;
        printf("Renderer %zu: sprite = %p, texture = %p\n", i, (void*)sprite, (void*)sprite->texture);

        if (sprite->texture && sprite->texture->sdl_texture) {
            // Trouvez ou créez le groupe pour ce z_index
            ZGroup* group = NULL;
            for (size_t j = 0; j < z_count; j++) {
                if (z_groups[j].z_index == renderer->z_index) {
                    group = &z_groups[j];
                    break;
                }
            }
            if (!group) {
                group = &z_groups[z_count++];
                group->z_index = renderer->z_index;
                group->merged_texture = SDL_CreateTexture(manager->sdl_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, window_width, window_height);
                if (!group->merged_texture) {
                    printf("RendererManager_Flatten: Erreur de création de la texture fusionnée pour z_index %d\n", renderer->z_index);
                    return;
                }
                printf("Created merged texture for z_index %d\n", renderer->z_index);
            }

            // Render the sprite's texture onto the merged texture
            if (SDL_SetRenderTarget(manager->sdl_renderer, group->merged_texture) != 0) {
                printf("RendererManager_Flatten: Erreur lors de SDL_SetRenderTarget pour z_index %d: %s\n", renderer->z_index, SDL_GetError());
                continue;
            }

            SDL_Rect target = {sprite->transform->position->x, sprite->transform->position->y, sprite->transform->size->width, sprite->transform->size->height};
            if (SDL_RenderCopy(manager->sdl_renderer, sprite->texture->sdl_texture, NULL, &target) != 0) {
                printf("RendererManager_Flatten: Erreur lors de SDL_RenderCopy pour z_index %d: %s\n", renderer->z_index, SDL_GetError());
                continue;
            }

            printf("Rendered sprite texture to merged texture for z_index %d\n", renderer->z_index);

            // Supprimez la texture originale
            SDL_DestroyTexture(sprite->texture->sdl_texture);
            free(sprite->texture);
            sprite->texture = NULL;
        }
    }

    // Remettre la cible de rendu à la fenêtre principale
    SDL_SetRenderTarget(manager->sdl_renderer, NULL);

    // Remplacez les anciennes textures par les nouvelles textures fusionnées
    for (size_t i = 0; i < z_count; i++) {
        ZGroup* group = &z_groups[i];
        Texture* new_texture = (Texture*)malloc(sizeof(Texture));
        if (!new_texture) {
            printf("RendererManager_Flatten: Erreur d'allocation de mémoire pour Texture\n");
            continue;
        }
        new_texture->sdl_texture = group->merged_texture;
        new_texture->size = Size2D_Init(window_width, window_height);

        printf("New merged texture created for z_index %d\n", group->z_index);

        for (size_t j = 1; j < manager->current_renderer_count - 1; j++) {
            Renderer* renderer = manager->renderers[j];
            if (renderer->z_index == group->z_index) {
                Sprite* sprite = (Sprite*)renderer->object;
                sprite->texture = new_texture;
                printf("Updated sprite texture for renderer %zu, z_index %d\n", j, group->z_index);
            }
        }
    }
}


// Fonction pour rendre tous les Renderers dans le RendererManager
void RendererManager_Render(RendererManager* manager) {
    SDL_RenderClear(manager->sdl_renderer);

    for (int i = 0; i < manager->current_renderer_count; i++) {
        Renderer* renderer = manager->renderers[i];

        //printf("RendererManager_Render: Rendering %d/%d\n", i, manager->current_renderer_count-1);
        
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
        
        //printf("RendererManager_Render: Success for %d/%d\n", i+1, manager->current_renderer_count);
    }

    SDL_RenderPresent(manager->sdl_renderer);
}

void Renderer_DynamicAnimation(Renderer* renderer, SDL_Renderer* sdl_renderer) {
    DynamicAnimation* dynamic_animation = (DynamicAnimation*)(renderer->object);
    if (!dynamic_animation) {
        fprintf(stderr, "Renderer_DynamicAnimation: dynamic_animation is NULL\n");
        return;
    }

    AnimationSettings* animation_settings = dynamic_animation->animation_settings;
    if (animation_settings == NULL) {
        printf("Renderer_DynamicAnimation: Error settings empty\n");
        return;
    }

    if (!animation_settings->is_playing) {
        return;
    }

    int current_time = SDL_GetTicks();
    int elapsed_time = current_time - animation_settings->last_frame_time;

    // Gestion du timing des frames
    if (elapsed_time >= animation_settings->speed) {
        elapsed_time = elapsed_time % animation_settings->speed;
        animation_settings->last_frame_time = current_time - elapsed_time;

        animation_settings->current_frame++;
        if (animation_settings->current_frame >= animation_settings->max_frame) {
            if (animation_settings->repeat == 0) {
                animation_settings->current_frame = animation_settings->max_frame - 1;
                animation_settings->is_playing = false;
            } else if (animation_settings->repeat == 1) {
                animation_settings->current_frame = 0;
            } else if (animation_settings->repeat == 2) {
                animation_settings->is_playing = false;
            } else if (animation_settings->repeat == 3) {
                animation_settings->current_frame = 0;
            }
        }
    }

    // Progression proportionnelle à l'animation
    float progress = (float)elapsed_time / animation_settings->speed;

    if (!animation_settings->is_playing) {
        return;
    }

    // Obtenir les frames courantes et suivantes
    AnimationFrame* curr_frame = dynamic_animation->startFrames[animation_settings->current_frame];
    AnimationFrame* next_frame = dynamic_animation->startFrames[(animation_settings->current_frame + 1) % animation_settings->max_frame];

    if (!curr_frame || !next_frame) {
        fprintf(stderr, "Renderer_DynamicAnimation: curr_frame ou next_frame est NULL\n");
        return;
    }

    // Calcul des positions et tailles interpolées
    Point2D* start_position = curr_frame->transform->position;
    Point2D* end_position = dynamic_animation->endFrames[animation_settings->current_frame]->transform->position;
    Size2D* start_size = curr_frame->transform->size;
    Size2D* end_size = dynamic_animation->endFrames[animation_settings->current_frame]->transform->size;

    SDL_Rect interpolated_position;

    if (animation_settings->repeat == 0 && animation_settings->current_frame == animation_settings->max_frame-1) {
        animation_settings->is_playing = false;
        return;
    } else if (animation_settings->repeat == 1 && animation_settings->current_frame == animation_settings->max_frame-1) {
        curr_frame = dynamic_animation->startFrames[0];
        next_frame = dynamic_animation->startFrames[1];
        animation_settings->current_frame = 0;
    } else if (animation_settings->repeat == 2 && !animation_settings->is_playing) {
        return;
    }

    interpolated_position.x = start_position->x + (int)((end_position->x - start_position->x) * progress);
    interpolated_position.y = start_position->y + (int)((end_position->y - start_position->y) * progress);
    interpolated_position.w = start_size->width + (int)((end_size->width - start_size->width) * progress);
    interpolated_position.h = start_size->height + (int)((end_size->height - start_size->height) * progress);

    // Rendu de la texture interpolée
    if (SDL_RenderCopy(sdl_renderer, curr_frame->texture->sdl_texture, NULL, &interpolated_position) != 0) {
        fprintf(stderr, "Renderer_DynamicAnimation: SDL_RenderCopy error: %s\n", SDL_GetError());
    }
}

void Renderer_StaticAnimation(Renderer* renderer, SDL_Renderer* sdl_renderer) {
    StaticAnimation* static_animation = (StaticAnimation*)(renderer->object);
    if (!static_animation) {
        fprintf(stderr, "Renderer_StaticAnimation: static_animation is NULL\n");
        return;
    }

    AnimationSettings* animation_settings = static_animation->animation_settings;
    if (animation_settings == NULL) {
        printf("Renderer_StaticAnimation: Error settings empty\n");
        return;
    }

    if (!animation_settings->is_playing) {
        return;
    }

    int current_time = SDL_GetTicks();
    int elapsed_time = current_time - animation_settings->last_frame_time;

    // Si le temps écoulé est supérieur à la vitesse de l'animation, remettre à zéro
    if (elapsed_time >= animation_settings->speed) {
        elapsed_time = elapsed_time % animation_settings->speed;  // Réinitialiser le temps écoulé
        animation_settings->last_frame_time = current_time - elapsed_time;  // Mettre à jour lastUpdateTime

        // Passer à la frame suivante
        animation_settings->current_frame++;
        if (animation_settings->current_frame >= animation_settings->max_frame) {

            if (animation_settings->repeat == 2) {
                animation_settings->is_playing = false;
            }
            if (animation_settings->repeat == 3) {
                animation_settings->current_frame = 0;
            }
        }
    }

    // Progression proportionnelle à l'animation
    float progress = (float)elapsed_time / animation_settings->speed;

    // Obtenir les frames de départ et de fin
    AnimationFrame* start_frame = static_animation->frames[animation_settings->current_frame];
    AnimationFrame* end_frame = static_animation->frames[(animation_settings->current_frame + 1) % animation_settings->max_frame];
    printf("Renderer_StaticAnimation: curr frame : %d\n", animation_settings->current_frame);
    if (!start_frame || !end_frame) {
        fprintf(stderr, "Renderer_StaticAnimation: start_frame ou end_frame est NULL\n");
        return;
    }

    // Calcul des positions et tailles interpolées
    SDL_Rect interpolated_position;

    if (animation_settings->repeat == 0 && animation_settings->current_frame == animation_settings->max_frame-1) {
        animation_settings->is_playing = false;
        return;

    } else if (animation_settings->repeat == 1 && animation_settings->current_frame == animation_settings->max_frame-1) {
        start_frame = static_animation->frames[0];
        end_frame = static_animation->frames[1];
        animation_settings->current_frame = 0;

    }  else if (animation_settings->repeat == 2 && !animation_settings->is_playing) {
        return;
    }

    interpolated_position.x = start_frame->transform->position->x + (int)((end_frame->transform->position->x - start_frame->transform->position->x) * progress);
    interpolated_position.y = start_frame->transform->position->y + (int)((end_frame->transform->position->y - start_frame->transform->position->y) * progress);
    interpolated_position.w = start_frame->transform->size->width + (int)((end_frame->transform->size->width - start_frame->transform->size->width) * progress);
    interpolated_position.h = start_frame->transform->size->height + (int)((end_frame->transform->size->height - start_frame->transform->size->height) * progress);


    // Rendre la frame actuelle
    if (SDL_RenderCopy(sdl_renderer, start_frame->texture->sdl_texture, NULL, &interpolated_position) != 0) {
        fprintf(stderr, "Renderer_StaticAnimation: SDL_RenderCopy error: %s\n", SDL_GetError());
    } 
}

void Renderer_Sprite(Renderer* renderer, SDL_Renderer* sdl_renderer) {
    Sprite* sprite = (Sprite*)(renderer->object);

    if (!renderer || !sprite || !sprite->texture || !sprite->texture->sdl_texture || !sprite->transform) {
        printf("Sprite_RenderStatic: Erreur pendant l'affichage, pointeurs invalides\n\t%s\n", SDL_GetError());
        return;
    }

    SDL_Rect target;
    target.x = sprite->transform->position->x;
    target.y = sprite->transform->position->y;
    target.w = sprite->transform->size->width;
    target.h = sprite->transform->size->height;

    SDL_RenderCopyEx(sdl_renderer, sprite->texture->sdl_texture, NULL, &target, sprite->transform->angle, (SDL_Point*)sprite->transform->center, sprite->transform->flip);

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
        // Créez un renderer pour chaque StaticAnimation
        Renderer temp_renderer;
        temp_renderer.renderFunction = renderer->renderFunction; // Utilisez la même fonction de rendu
        temp_renderer.object = manager->static_animations[i];    // Associez le StaticAnimation correspondant

        Renderer_StaticAnimation(&temp_renderer, sdl_renderer);
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