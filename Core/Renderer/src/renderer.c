#include "../include/renderer.h"

RendererManager* RendererManager_Init(SDL_Renderer* sdl_renderer, int max_renderers) {

    if (sdl_renderer == NULL) {
        sdl_renderer = SDL_Renderer_Current();
    }

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

void RendererManager_Add(RendererManager* manager, ...) {
    va_list args;
    va_start(args, manager);

    int num_renderers = 0;
    Renderer* renderer;

    // Compter les arguments variadiques jusqu'à rencontrer NULL
    while ((renderer = va_arg(args, Renderer*)) != NULL) {
        num_renderers++;
    }
    va_end(args);
    va_start(args, manager); // Réinitialiser va_list pour réutilisation

    for (int i = 0; i < num_renderers; i++) {
        
        renderer = va_arg(args, Renderer*);

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

void RendererManager_Flatten(RendererManager* manager) {
    // Vérification de la validité du manager et de son tableau de renderers
    if (!manager || !manager->renderers) {
        printf("mergeTexturesByZIndex: Erreur - manager ou manager->renderers est NULL\n");
        return;
    }

    // Assurez-vous que le premier renderer est la fenêtre
    Window* window = manager->renderers[0]->object;
    if (!window) {
        printf("mergeTexturesByZIndex: Erreur - le renderer de la fenêtre est NULL\n");
        return;
    }

    int window_width = window->texture->size->width;
    int window_height = window->texture->size->height;
    printf("window_width: %d ; window_height: %d\n", window_width, window_height);

    // Utilisation d'un tableau pour garder une référence des textures fusionnées par z_index
    Texture* mergedTextures[MAX_RENDERED_OBJECTS]; // Supposer un maximum pour éviter de dépasser la capacité de la mémoire

    // Initialisation du tableau à NULL
    for (int i = 0; i < MAX_RENDERED_OBJECTS; i++) {
        mergedTextures[i] = NULL;
    }

    // Parcourir chaque renderer dans le tableau
    for (size_t i = 1; i < manager->current_renderer_count; i++) {
        Renderer* renderer = manager->renderers[i];
        printf("Renderer %zu: renderer = %p\n", i, (void*)renderer);

        // Vérifier si le renderer et son objet sont valides
        if (!renderer || !renderer->object) {
            printf("mergeTexturesByZIndex: Renderer ou renderer->object est NULL à l'indice %zu\n", i);
            continue;
        }

        // Vérification si l'objet est un Sprite
        Sprite* sprite = (Sprite*)renderer->object;
        if (sprite->texture && sprite->texture->sdl_texture) {
            printf("Renderer %zu: sprite = %p, texture = %p, z_index = %d\n", i, (void*)sprite, (void*)sprite->texture, renderer->z_index);
            
            // Vérifier si une texture fusionnée existe déjà pour ce z_index
            if (!mergedTextures[renderer->z_index]) {
                printf("Texture fusionné n'existe pas\n");
                // Créer une nouvelle texture pour ce z_index
                mergedTextures[renderer->z_index] = (Texture*)malloc(sizeof(Texture));
                if (!mergedTextures[renderer->z_index]) {
                    printf("mergeTexturesByZIndex: Erreur d'allocation de mémoire pour Texture\n");
                    continue;
                }
                mergedTextures[renderer->z_index]->sdl_texture = SDL_CreateTexture(manager->sdl_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, window_width, window_height);
                if (!mergedTextures[renderer->z_index]->sdl_texture) {
                    printf("mergeTexturesByZIndex: Erreur de création de la texture fusionnée pour z_index %d\n", renderer->z_index);
                    free(mergedTextures[renderer->z_index]);
                    mergedTextures[renderer->z_index] = NULL;
                    continue;
                }
                mergedTextures[renderer->z_index]->size = Size2D_Init(window_width, window_height);

                printf("Created merged texture for z_index %d\n", renderer->z_index);
            }
            printf("Texture fusionné existe\n");
            // Définir la texture fusionnée comme la cible de rendu
            if (SDL_SetRenderTarget(manager->sdl_renderer, mergedTextures[renderer->z_index]->sdl_texture) != 0) {
                printf("mergeTexturesByZIndex: Erreur lors de SDL_SetRenderTarget pour z_index %d: %s\n", renderer->z_index, SDL_GetError());
                continue;
            }

            printf("Texture fusionné défini comme cible \n");

            // Rendre la texture du sprite sur la texture fusionnée
            SDL_Rect target = {sprite->transform->position->x, sprite->transform->position->y, sprite->transform->size->width, sprite->transform->size->height};
            
            printf("coordonnes définis : x = %d, y = %d, width = %d, height = %d\n", target.x, target.y, target.w, target.h);

            // Ajouter des vérifications pour manager->sdl_renderer et sprite->texture->sdl_texture
            if (!manager->sdl_renderer) {
                printf("mergeTexturesByZIndex: Erreur - sdl_renderer est NULL\n");
                continue;
            }
            if (!sprite->texture->sdl_texture) {
                printf("mergeTexturesByZIndex: Erreur - sdl_texture est NULL\n");
                continue;
            }

            if (SDL_RenderCopy(manager->sdl_renderer, sprite->texture->sdl_texture, NULL, &target) != 0) {
                printf("mergeTexturesByZIndex: Erreur lors de SDL_RenderCopy pour z_index %d: %s\n", renderer->z_index, SDL_GetError());
                continue;
            }

            printf("Rendered sprite texture to merged texture for z_index %d\n", renderer->z_index);

            // Détruire la texture originale du sprite
            SDL_DestroyTexture(sprite->texture->sdl_texture);
            free(sprite->texture);
            sprite->texture = NULL;
        }
    }

    // Remettre la cible de rendu à la fenêtre principale
    SDL_SetRenderTarget(manager->sdl_renderer, NULL);

    // Remplacer les anciennes textures par les nouvelles textures fusionnées
    for (int i = 1; i < manager->current_renderer_count; i++) {
        Renderer* renderer = manager->renderers[i];
        if (renderer && renderer->object) {
            // Vérifier le type de l'objet
            Sprite* sprite = (Sprite*)renderer->object;
            if (sprite->texture && sprite->texture->sdl_texture) {

                if (sprite->texture && sprite->texture->sdl_texture) {
                    int z_index = renderer->z_index;
                    if (z_index < MAX_RENDERED_OBJECTS) {
                        sprite->texture = mergedTextures[z_index];
                        printf("Updated sprite texture for renderer %d ; z_index %d\n", i, z_index);
                    } else {
                        printf("Renderer z_index %d dépasse la taille maximale de mergedTextures\n", z_index);
                    }
                } else {
                    printf("La texture de l'objet n'est pas valide pour renderer %d\n", i);
                }
            } else {
                printf("L'objet n'est pas un sprite pour renderer %d\n", i);
            }
        } else {
            printf("Renderer ou renderer->object est NULL à l'indice %d\n", i);
        }
    }

}

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

void Renderer_Widget(Renderer* renderer, SDL_Renderer* sdl_renderer) {
    Widget* widget = (Widget*)(renderer->object);

    if (!renderer || !widget || !widget->texture || !widget->texture->sdl_texture || !widget->transform) {
        printf("Renderer_Widget: Erreur pendant l'affichage, pointeurs invalides\n\t%s\n", SDL_GetError());
        return;
    }

    SDL_Rect target;
    target.x = widget->transform->position->x;
    target.y = widget->transform->position->y;
    target.w = widget->transform->size->width;
    target.h = widget->transform->size->height;

    SDL_RenderCopyEx(sdl_renderer, widget->texture->sdl_texture, NULL, &target, widget->transform->angle, (SDL_Point*)widget->transform->center, widget->transform->flip);
}

void Renderer_Panel(Renderer* renderer, SDL_Renderer* sdl_renderer) {
    Panel* panel = (Panel*)(renderer->object);

    if (!renderer || !panel || !panel->texture || !panel->texture->sdl_texture || !panel->transform) {
        printf("Sprite_RenderStatic: Erreur pendant l'affichage, pointeurs invalides\n\t%s\n", SDL_GetError());
        return;
    }

    SDL_Rect target;
    target.x = panel->transform->position->x;
    target.y = panel->transform->position->y;
    target.w = panel->transform->size->width;
    target.h = panel->transform->size->height;

    SDL_RenderCopyEx(sdl_renderer, panel->texture->sdl_texture, NULL, &target, panel->transform->angle, (SDL_Point*)panel->transform->center, panel->transform->flip);
}

void Renderer_Label(Renderer* renderer, SDL_Renderer* sdl_renderer) {
    if (!renderer || !renderer->object) {
        printf("Renderer_Label: Renderer ou objet invalide\n\t%s\n", SDL_GetError());
        return;
    }

    Label* label = (Label*)(renderer->object);

    if (!label->transform) {
        printf("Renderer_Label: Transform invalide\n\t%s\n", SDL_GetError());
        return;
    }

    if (!label->font) {
        printf("Renderer_Label: Font invalide\n\t%s\n", SDL_GetError());
        return;
    }

    SDL_Rect target;
    target.x = label->transform->position->x;
    target.y = label->transform->position->y;
    target.w = label->transform->size->width;
    target.h = label->transform->size->height;

    // Dessiner la texture de fond, si elle existe
    if (label->texture && label->texture->sdl_texture) {
        SDL_RenderCopy(sdl_renderer, label->texture->sdl_texture, NULL, &target);
    }

    // Dessiner le texte
    if (label->text && label->text[0] != '\0') {
        SDL_Color sdl_color = Color_GetSDL(*label->font->color);
        //printf("RENDERER_LABEL_SDL_Color: r=%u, g=%u, b=%u, a=%u\n", sdl_color.r, sdl_color.g, sdl_color.b, sdl_color.a);
        char* text = label->text;
        char* line_start = text;
        char* line_end = NULL;
        int line_height = TTF_FontHeight(label->font->sdl_font);
        int y_offset = target.y;

        // Compter le nombre de lignes pour centrer verticalement
        int num_lines = 0;
        while ((line_end = strchr(line_start, '\n')) != NULL) {
            num_lines++;
            line_start = line_end + 1;
        }
        if (*line_start != '\0') {
            num_lines++;
        }

        int total_text_height = num_lines * line_height;
        y_offset = target.y; 
        line_start = text;

        while ((line_end = strchr(line_start, '\n')) != NULL) {
            int line_length = line_end - line_start;
            char line[line_length + 1];
            strncpy(line, line_start, line_length);
            line[line_length] = '\0';

            SDL_Surface* text_surface = TTF_RenderText_Blended(label->font->sdl_font, line, sdl_color);
            if (!text_surface) {
                fprintf(stderr, "Renderer_Label: Échec de la création de la surface de texte\n\t%s\n", SDL_GetError());
                continue;
            }

            SDL_Texture* text_texture = SDL_CreateTextureFromSurface(sdl_renderer, text_surface);
            if (!text_texture) {
                fprintf(stderr, "Renderer_Label: Échec de la création de la texture de texte\n\t%s\n", SDL_GetError());
                SDL_FreeSurface(text_surface);
                continue;
            }

            SDL_Rect text_rect;
            text_rect.x = target.x + 5; // Ajuster le texte pour qu'il soit légèrement à l'intérieur
            text_rect.y = y_offset;
            text_rect.w = text_surface->w;
            text_rect.h = text_surface->h;

            SDL_RenderCopy(sdl_renderer, text_texture, NULL, &text_rect);

            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(text_texture);

            y_offset += line_height;
            line_start = line_end + 1;
        }

        // Rendre la dernière ligne
        if (*line_start != '\0') {
            SDL_Surface* text_surface = TTF_RenderText_Blended(label->font->sdl_font, line_start, sdl_color);
            if (!text_surface) {
                fprintf(stderr, "Renderer_Label: Échec de la création de la surface de texte\n\t%s\n", SDL_GetError());
                return;
            }

            SDL_Texture* text_texture = SDL_CreateTextureFromSurface(sdl_renderer, text_surface);
            if (!text_texture) {
                fprintf(stderr, "Renderer_Label: Échec de la création de la texture de texte\n\t%s\n", SDL_GetError());
                SDL_FreeSurface(text_surface);
                return;
            }

            SDL_Rect text_rect;
            text_rect.x = target.x + 5; // Ajuster le texte pour qu'il soit légèrement à l'intérieur
            text_rect.y = y_offset;
            text_rect.w = text_surface->w;
            text_rect.h = text_surface->h;

            SDL_RenderCopy(sdl_renderer, text_texture, NULL, &text_rect);

            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(text_texture);
        }
    }
}



void Renderer_Button(Renderer* renderer, SDL_Renderer* sdl_renderer) {
    if (!renderer || !renderer->object) {
        printf("Renderer_Button: Renderer ou objet invalide\n\t%s\n", SDL_GetError());
        return;
    }

    Button* button = (Button*)(renderer->object);

    if (!button->transform) {
        printf("Renderer_Button: Transform invalide\n\t%s\n", SDL_GetError());
        return;
    }

    SDL_Rect target;
    target.x = button->transform->position->x;
    target.y = button->transform->position->y;
    target.w = button->transform->size->width;
    target.h = button->transform->size->height;

    // Dessiner la texture de fond, si elle existe
    if (button->texture && button->texture->sdl_texture) {
        SDL_RenderCopy(sdl_renderer, button->texture->sdl_texture, NULL, &target);
    }

}

void Renderer_InputField(Renderer* renderer, SDL_Renderer* sdl_renderer) {
    if (!renderer || !renderer->object) {
        printf("Renderer_InputField: Renderer ou objet invalide\n\t%s\n", SDL_GetError());
        return;
    }

    InputField* input_field = (InputField*)(renderer->object);

    if (!input_field->transform) {
        printf("Renderer_InputField: Transform invalide\n\t%s\n", SDL_GetError());
        return;
    }

    if (!input_field->font) {
        printf("Renderer_InputField: Font invalide\n\t%s\n", SDL_GetError());
        return;
    }

    SDL_Rect target;
    target.x = input_field->transform->position->x;
    target.y = input_field->transform->position->y;
    target.w = input_field->transform->size->width;
    target.h = input_field->transform->size->height;

    // Dessiner la texture de fond, si elle existe
    if (input_field->texture && input_field->texture->sdl_texture) {
        SDL_RenderCopy(sdl_renderer, input_field->texture->sdl_texture, NULL, &target);
    }

    // Dessiner le texte
    if (input_field->text && input_field->text[0] != '\0') {
        SDL_Color sdl_color = { input_field->font->color->r, input_field->font->color->g, input_field->font->color->b, input_field->font->color->a };
        char* text = input_field->text;
        char* line_start = text;
        char* line_end = NULL;
        int line_height = TTF_FontHeight(input_field->font->sdl_font);
        int y_offset = target.y;

        // Compter le nombre de lignes pour centrer verticalement
        int num_lines = 0;
        while ((line_end = strchr(line_start, '\n')) != NULL) {
            num_lines++;
            line_start = line_end + 1;
        }
        if (*line_start != '\0') {
            num_lines++;
        }

        // Centrer verticalement
        int total_text_height = num_lines * line_height;
        int y_start = target.y + 5;

        line_start = text;
        y_offset = y_start;

        while ((line_end = strchr(line_start, '\n')) != NULL) {
            int line_length = line_end - line_start;
            char line[line_length + 1];
            strncpy(line, line_start, line_length);
            line[line_length] = '\0';

            SDL_Surface* text_surface = TTF_RenderText_Blended(input_field->font->sdl_font, line, sdl_color);
            SDL_Texture* text_texture = SDL_CreateTextureFromSurface(sdl_renderer, text_surface);

            SDL_Rect text_rect;
            text_rect.x = target.x + 5; // Ajuster le texte pour qu'il soit légèrement à l'intérieur
            text_rect.y = y_offset;
            text_rect.w = text_surface->w;
            text_rect.h = text_surface->h;

            SDL_RenderCopy(sdl_renderer, text_texture, NULL, &text_rect);

            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(text_texture);

            y_offset += line_height;
            line_start = line_end + 1;
        }

        // Rendre la dernière ligne
        if (*line_start != '\0') {
            SDL_Surface* text_surface = TTF_RenderText_Blended(input_field->font->sdl_font, line_start, sdl_color);
            SDL_Texture* text_texture = SDL_CreateTextureFromSurface(sdl_renderer, text_surface);

            SDL_Rect text_rect;
            text_rect.x = target.x + 5; // Ajuster le texte pour qu'il soit légèrement à l'intérieur
            text_rect.y = y_offset;
            text_rect.w = text_surface->w;
            text_rect.h = text_surface->h;

            SDL_RenderCopy(sdl_renderer, text_texture, NULL, &text_rect);

            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(text_texture);
        }
    }
}

void Renderer_Tooltip(Renderer* renderer, SDL_Renderer* sdl_renderer) {
    if (!renderer || !renderer->object) {
        printf("Renderer_Tooltip: Renderer ou objet invalide\n\t%s\n", SDL_GetError());
        return;
    }

    Tooltip* tooltip = (Tooltip*)(renderer->object);

    if (tooltip->is_visible == 0) {
        return;
    }
    
    if (!tooltip->transform) {
        printf("Renderer_Tooltip: Transform invalide\n\t%s\n", SDL_GetError());
        return;
    }

    if (!tooltip->font) {
        printf("Renderer_Tooltip: Font invalide\n\t%s\n", SDL_GetError());
        return;
    }

    SDL_Rect target;
    target.x = tooltip->transform->position->x;
    target.y = tooltip->transform->position->y;
    target.w = tooltip->transform->size->width;
    target.h = tooltip->transform->size->height;

    // Dessiner la texture de fond, si elle existe
    if (tooltip->texture && tooltip->texture->sdl_texture) {
        SDL_RenderCopy(sdl_renderer, tooltip->texture->sdl_texture, NULL, &target);
    }

    // Dessiner le texte
    if (tooltip->text && tooltip->text[0] != '\0') {
        SDL_Color sdl_color = { tooltip->font->color->r, tooltip->font->color->g, tooltip->font->color->b, tooltip->font->color->a };
        SDL_Surface* text_surface = TTF_RenderText_Blended(tooltip->font->sdl_font, tooltip->text, sdl_color);
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(sdl_renderer, text_surface);

        SDL_Rect text_rect;
        text_rect.x = target.x + 5; // Ajuster le texte pour qu'il soit légèrement à l'intérieur
        text_rect.y = target.y + 5; // Ajuster le texte pour qu'il soit légèrement à l'intérieur
        text_rect.w = text_surface->w;
        text_rect.h = text_surface->h;

        // Si le texte dépasse la largeur de la tooltip, on ajuste la largeur
        if (text_rect.w > target.w - 10) {
            text_rect.w = target.w - 10;
        }

        // Si le texte dépasse la hauteur de la tooltip, on ajuste la hauteur
        if (text_rect.h > target.h - 10) {
            text_rect.h = target.h - 10;
        }

        SDL_RenderCopy(sdl_renderer, text_texture, NULL, &text_rect);

        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);
    }
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

void RendererManager_Sort(RendererManager* manager) {
    Renderer_Sort_MergeRecursive(manager->renderers, 0, manager->current_renderer_count - 1);
}

void Renderer_Sort_Merge(Renderer** renderers, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Tableaux temporaires
    Renderer* L[n1];
    Renderer* R[n2];

    // Copier les données dans les tableaux temporaires L et R
    for (i = 0; i < n1; i++)
        L[i] = renderers[l + i];
    for (j = 0; j < n2; j++)
        R[j] = renderers[m + 1 + j];

    // Fusionner les tableaux temporaires L et R en renderers[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i]->z_index <= R[j]->z_index) {
            renderers[k] = L[i];
            i++;
        } else {
            renderers[k] = R[j];
            j++;
        }
        k++;
    }

    // Copier les éléments restants de L[] si il y en a 
    while (i < n1) {
        renderers[k] = L[i];
        i++;
        k++;
    }

    // Copier les éléments restants de R[] si il y en a
    while (j < n2) {
        renderers[k] = R[j];
        j++;
        k++;
    }
}

void Renderer_Sort_MergeRecursive(Renderer** renderers, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Trier les deux moitiés
        Renderer_Sort_MergeRecursive(renderers, l, m);
        Renderer_Sort_MergeRecursive(renderers, m + 1, r);

        // Fusionner les deux moitiés triées
        Renderer_Sort_Merge(renderers, l, m, r);
    }
}