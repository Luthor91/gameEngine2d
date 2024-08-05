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


void apply_operator(char operator, int* result, int current_value) {
    if (operator == '+') {
        *result += current_value;
    } else if (operator == '-') {
        *result -= current_value;
    }
}

void handle_percentage(const char* param_name, int percent, int object_value, int* current_value, int window_width, int window_height) {
    if (strcmp(param_name, "size") == 0) {
        *current_value = object_value * percent / 100;
    } else if (strcmp(param_name, "posx") == 0 || strcmp(param_name, "cposx") == 0) {
        *current_value = window_width * percent / 100;
        if (strcmp(param_name, "cposx") == 0) {
            *current_value -= object_value / 2;
        }
    } else if (strcmp(param_name, "posy") == 0 || strcmp(param_name, "cposy") == 0) {
        *current_value = window_height * percent / 100;
        if (strcmp(param_name, "cposy") == 0) {
            *current_value -= object_value / 2;
        }
    }
}

int Parse_Expression(const char* expr, int object_value, const char* param_name) {
    int result = 0;
    int current_value = 0;
    char operator = '+';
    char buf[128];
    int i = 0;
    int window_width = DEFAULT_WINDOW_WIDTH;
    int window_height = DEFAULT_WINDOW_HEIGHT;

    // Check if the expression contains any operators
    int contains_operator = 0;
    for (int k = 0; expr[k] != '\0'; k++) {
        if (expr[k] == '+' || expr[k] == '-') {
            contains_operator = 1;
            break;
        }
    }

    while (expr[i] != '\0') {
        if (expr[i] == '+' || expr[i] == '-') {
            // Apply the previous operation
            apply_operator(operator, &result, current_value);
            operator = expr[i];
            current_value = 0;
        } else {
            int j = 0;
            memset(buf, 0, sizeof(buf)); // Clear buffer

            if (expr[i] == '&') {
                i++;
                while (isdigit(expr[i])) {
                    buf[j++] = expr[i++];
                }
                buf[j] = '\0';
                current_value = atoi(buf);
                if (expr[i] == '%') {
                    current_value = object_value * current_value / 100;
                    i++;
                }
            } else if (expr[i] == 'w' || expr[i] == 'h') {
                char dimension = expr[i++];
                while (isdigit(expr[i])) {
                    buf[j++] = expr[i++];
                }
                buf[j] = '\0';
                int percent = atoi(buf);
                if (expr[i] == '%') {
                    handle_percentage(param_name, percent, object_value, &current_value, window_width, window_height);
                    i++;
                } else {
                    current_value = atoi(buf);
                }
            } else if (strncmp(&expr[i], "right", 5) == 0) {
                current_value = window_width - object_value;
                i += 5;
            } else if (strncmp(&expr[i], "cright", 6) == 0) {
                current_value = window_width - object_value / 2;
                i += 6;
            } else if (strncmp(&expr[i], "left", 4) == 0) {
                current_value = 0;
                i += 4;
            } else if (strncmp(&expr[i], "cleft", 5) == 0) {
                current_value = object_value / 2;
                i += 5;
            } else if (strncmp(&expr[i], "top", 3) == 0) {
                current_value = 0;
                i += 3;
            } else if (strncmp(&expr[i], "ctop", 4) == 0) {
                current_value = object_value / 2;
                i += 4;
            } else if (strncmp(&expr[i], "cbottom", 7) == 0) {
                current_value = window_height - object_value / 2;
                i += 7;
            } else if (strncmp(&expr[i], "bottom", 6) == 0) {
                current_value = window_height - object_value;
                i += 6;
            } else if (strncmp(&expr[i], "centerx", 7) == 0) {
                current_value = window_width / 2 - object_value / 2;
                i += 7;
            } else if (strncmp(&expr[i], "centery", 7) == 0) {
                current_value = window_height / 2 - object_value / 2;
                i += 7;
            } else if (strncmp(&expr[i], "center", 6) == 0) {
                if (strcmp(param_name, "posx") == 0 || strcmp(param_name, "cposx") == 0) {
                    current_value = window_width / 2 - (strcmp(param_name, "cposx") == 0 ? object_value / 2 : 0);
                } else if (strcmp(param_name, "posy") == 0 || strcmp(param_name, "cposy") == 0) {
                    current_value = window_height / 2 - (strcmp(param_name, "cposy") == 0 ? object_value / 2 : 0);
                }
                i += 6;
            } else {
                while (isdigit(expr[i])) {
                    buf[j++] = expr[i++];
                }
                buf[j] = '\0';
                int percent = atoi(buf);
                if (expr[i] == '%') {
                    handle_percentage(param_name, percent, object_value, &current_value, window_width, window_height);
                    i++;
                } else {
                    current_value = atoi(buf);
                }
            }

            // Check for operators immediately following the value
            if (expr[i] == '+' || expr[i] == '-') {
                apply_operator(operator, &result, current_value);
                operator = expr[i];
                current_value = 0;
            } else if (!contains_operator) {
                return current_value;
            }
        }
        i++;
    }

    // Apply the last operation, if necessary
    if (contains_operator) {
        apply_operator(operator, &result, current_value);
    } else {
        result = current_value;
    }

    return result;
}
