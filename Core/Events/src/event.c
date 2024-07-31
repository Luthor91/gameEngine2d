#include "../include/event.h"

void Event_InputField(void* object, SDL_Event* event) {
    InputField* input_field = (InputField*)object;
    if (!input_field || !event) return;

    // Traitement des événements
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        int x = event->button.x;
        int y = event->button.y;

        if (x >= input_field->transform->position->x && x <= input_field->transform->position->x + input_field->transform->size->width &&
            y >= input_field->transform->position->y && y <= input_field->transform->position->y + input_field->transform->size->height) {
            input_field->is_focused = 1;
        } else {
            input_field->is_focused = 0;
        }
    }

    if (input_field->is_focused && event->type == SDL_TEXTINPUT) {
        int current_length = strlen(input_field->text);
        int new_length = current_length + strlen(event->text.text);

        // Check if new text would exceed width
        char temp_text[new_length + 1];
        strcpy(temp_text, input_field->text);
        strcat(temp_text, event->text.text);

        // Initialize variables for text dimensions
        int line_width = 0;
        int line_height;
        TTF_SizeText(input_field->font->sdl_font, "A", NULL, &line_height);

        int max_lines = input_field->transform->size->height / line_height;
        int current_line_count = 1;  // Start with one line

        for (int i = 0; i < new_length; i++) {
            int char_width;
            char current_char[2] = { temp_text[i], '\0' };  // Convert character to string
            TTF_SizeText(input_field->font->sdl_font, current_char, &char_width, NULL);

            if (temp_text[i] == '\n') {
                line_width = 0;
                current_line_count++;
            } else {
                line_width += char_width;
                if (line_width > input_field->transform->size->width - 5) {
                    line_width = char_width; // Start new line with current character
                    current_line_count++;
                    // Insert newline character
                    memmove(&temp_text[i + 1], &temp_text[i], strlen(&temp_text[i]) + 1);
                    temp_text[i] = '\n';
                    new_length++;
                }
            }
            if (current_line_count > max_lines) {
                return;
            }
        }

        // Append the new text
        strcpy(input_field->text, temp_text);
    }

    if (input_field->is_focused && event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_BACKSPACE && strlen(input_field->text) > 0) {
            input_field->text[strlen(input_field->text) - 1] = '\0';
        } else if (event->key.keysym.sym == SDLK_RETURN) {
            int current_length = strlen(input_field->text);

            int line_height;
            TTF_SizeText(input_field->font->sdl_font, "A", NULL, &line_height);

            int max_lines = input_field->transform->size->height / line_height;

            int current_line_count = 1;
            for (int i = 0; i < current_length; i++) {
                if (input_field->text[i] == '\n') {
                    current_line_count++;
                }
            }

            if (current_line_count < max_lines) {
                strcat(input_field->text, "\n");
            }
        }
    }
}

void Event_Button_Clicked(void* object, SDL_Event* event) {

    Button* button = (Button*)object; 

    if (!button || !event) return;

    // Traitement des événements
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        int x = event->button.x;
        int y = event->button.y;

        if (x >= button->transform->position->x && x <= button->transform->position->x + button->transform->size->width &&
            y >= button->transform->position->y && y <= button->transform->position->y + button->transform->size->height) {
                
            button->pressed = 1;  // Bouton pressé
            if (button->on_click) {
                button->on_click(button->data);  // Appeler la fonction on_click avec les données associées
            }
        }
    }
}

void Event_Widget_Dragged(void* object, SDL_Event* event) {

    Widget* widget = (Widget*)object; 
    if (!widget || !event) return;

    switch (event->type) {
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                int x = event->button.x;
                int y = event->button.y;
                if (x >= widget->transform->position->x && x <= widget->transform->position->x + widget->transform->size->width &&
                    y >= widget->transform->position->y && y <= widget->transform->position->y + widget->transform->size->height) {
                    widget->is_dragging = 1;
                    widget->drag_offset_x = x - widget->transform->position->x;
                    widget->drag_offset_y = y - widget->transform->position->y;
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event->button.button == SDL_BUTTON_LEFT) {
                widget->is_dragging = 0;
            }
            break;
        case SDL_MOUSEMOTION:
            if (widget->is_dragging) {
                widget->transform->position->x = event->motion.x - widget->drag_offset_x;
                widget->transform->position->y = event->motion.y - widget->drag_offset_y;
            }
            break;
    }
}

void Event_Tooltip_Hovered(void* object, SDL_Event* event) {
    Tooltip* tooltip = (Tooltip*)object;

    if (!tooltip || !event) return;

    // Traitement des événements
    if (event->type == SDL_MOUSEMOTION) {
        int x = event->motion.x;
        int y = event->motion.y;

        if (x >= tooltip->hitbox->position->x && x <= tooltip->hitbox->position->x + tooltip->hitbox->size->width &&
            y >= tooltip->hitbox->position->y && y <= tooltip->hitbox->position->y + tooltip->hitbox->size->height) {
            tooltip->is_visible = 1;  // La souris est sur le tooltip
        } else {
            tooltip->is_visible = 0;  // La souris n'est pas sur le tooltip
        }
    }
}