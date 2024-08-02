#include "../include/string.h"

char* String_Concat(const char* str1, const char* str2) {
    // Déterminer la taille requise pour la chaîne résultante
    size_t len = snprintf(NULL, 0, "%s%s", str1, str2) + 1;

    // Allouer de la mémoire pour la chaîne résultante
    char* result = (char*)malloc(len);
    if (result == NULL) {
        // Gestion de l'erreur d'allocation mémoire
        return NULL;
    }

    // Concaténer les chaînes
    snprintf(result, len, "%s%s", str1, str2);

    return result;
}

void CheckTextFit(Font* font, char* text, int maxWidth, int maxHeight) {
    if (!font || !text) return;

    int charHeight;
    TTF_SizeText(font->sdl_font, "A", NULL, &charHeight);

    int lineHeight = charHeight;
    int maxLines = maxHeight / lineHeight;
    int currentLineWidth = 0;
    int currentLine = 1;
    int lastSpaceIndex = -1;
    int lastSpaceLineWidth = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        int advanceWidth;
        char temp[2] = {text[i], '\0'};
        TTF_SizeText(font->sdl_font, temp, &advanceWidth, NULL);

        if (text[i] == ' ') {
            lastSpaceIndex = i;
            lastSpaceLineWidth = currentLineWidth;
        }

        currentLineWidth += advanceWidth;

        if (text[i] == '\n' || currentLineWidth > maxWidth) {
            if (text[i] != '\n' && lastSpaceIndex != -1) {
                text[lastSpaceIndex] = '\n';
                i = lastSpaceIndex;
                currentLineWidth = currentLineWidth - lastSpaceLineWidth;
                lastSpaceIndex = -1;
            } else {
                if (text[i] != '\n') {
                    memmove(&text[i + 1], &text[i], strlen(&text[i]) + 1);
                    text[i] = '\n';
                }
                currentLineWidth = 0;
            }
            currentLine++;
        }

        if (currentLine > maxLines) {
            text[i] = '\0';
            break;
        }
    }
}
