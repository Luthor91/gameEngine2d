#include "../include/parse.h"

void Parse_CleanParamName(char* param_name) {
    char* read_ptr = param_name;
    char* write_ptr = param_name;

    while (*read_ptr) {
        if (*read_ptr != ' ' && *read_ptr != '\\') {
            *write_ptr++ = *read_ptr;
        }
        read_ptr++;
    }
    *write_ptr = '\0';
}

int Parse_Color(Color* color, const char* str) {
    if (strcmp(str, "RED") == 0) {
        *color = COLOR_RED;
    } else if (strcmp(str, "GREEN") == 0) {
        *color = COLOR_GREEN;
    } else if (strcmp(str, "BLUE") == 0) {
        *color = COLOR_BLUE;
    } else if (strcmp(str, "WHITE") == 0) {
        *color = COLOR_WHITE;
    } else if (strcmp(str, "BLACK") == 0) {
        *color = COLOR_BLACK;
    } else if (strcmp(str, "YELLOW") == 0) {
        *color = COLOR_YELLOW;
    } else if (strcmp(str, "CYAN") == 0) {
        *color = COLOR_CYAN;
    } else if (strcmp(str, "MAGENTA") == 0) {
        *color = COLOR_MAGENTA;
    } else if (sscanf(str, "%hhd,%hhd,%hhd,%hhd", &color->r, &color->g, &color->b, &color->a) == 4) {
        return 1; // Successfully parsed RGBA color
    } else {
        return 0; // Invalid color format
    }
    return 1;
}

// Fonction pour évaluer les expressions en utilisant des variables et des opérations
int Parse_Expression(const char* expr, int object_value) {
    int result = 0;
    int current_value = 0;
    char operator = '+';
    char buf[128];
    int i = 0;
    int window_width = DEFAULT_WINDOW_WIDTH;
    int window_height = DEFAULT_WINDOW_HEIGHT;
    while (expr[i] != '\0') {
        if (expr[i] == '+' || expr[i] == '-') {
            if (i > 0) {
                // Appliquer l'opération précédente
                if (operator == '+') {
                    result += current_value;
                } else {
                    result -= current_value;
                }
            }
            // Mémoriser l'opérateur actuel
            operator = expr[i];
            current_value = 0;
        } else {
            // Traitement des valeurs et références
            int j = 0;
            if (expr[i] == '&') {
                // Valeur de l'objet référencée
                i++;
                while (isdigit(expr[i])) {
                    buf[j++] = expr[i++];
                }
                buf[j] = '\0';
                current_value = object_value * (atoi(buf) / 100);
            } else if (expr[i] == 'w' || expr[i] == 'h') {
                // Valeur de la fenêtre référencée
                char dimension = expr[i++];
                while (isdigit(expr[i])) {
                    buf[j++] = expr[i++];
                }
                buf[j] = '\0';
                int percent = atoi(buf);
                if (dimension == 'w') {
                    current_value = window_width * percent / 100;
                } else if (dimension == 'h') {
                    current_value = window_height * percent / 100;
                }
            } else {
                // Valeur numérique directe
                while (isdigit(expr[i])) {
                    buf[j++] = expr[i++];
                }
                buf[j] = '\0';
                current_value = atoi(buf);
            }
            // Appliquer l'opération accumulée
            if (i > 0 && (operator == '+' || operator == '-')) {
                if (operator == '+') {
                    result += current_value;
                } else {
                    result -= current_value;
                }
                current_value = 0;
            }
        }
        i++;
    }
    // Appliquer la dernière opération
    if (operator == '+') {
        result += current_value;
    } else {
        result -= current_value;
    }
    
    return result;
}
