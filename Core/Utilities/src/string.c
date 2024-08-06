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

    // Variables pour les dimensions des caractères
    int charWidth, charHeight;
    TTF_SizeText(font->sdl_font, "A", &charWidth, &charHeight);

    int lineHeight = charHeight;
    int maxLines = maxHeight / lineHeight;
    int currentLineWidth = 0;
    int currentLine = 1;
    int lastSpaceIndex = -1;
    int lastSpaceLineWidth = 0;

    int length = strlen(text);
    char temp_text[length + 1];
    strcpy(temp_text, text);

    for (int i = 0; i < length; i++) {
        char currentChar[2] = { temp_text[i], '\0' }; // Convertir le caractère en chaîne
        TTF_SizeText(font->sdl_font, currentChar, &charWidth, NULL);

        if (temp_text[i] == ' ') {
            lastSpaceIndex = i;
            lastSpaceLineWidth = currentLineWidth;
        }

        currentLineWidth += charWidth;

        if (temp_text[i] == '\n' || currentLineWidth > maxWidth - 5) {
            if (temp_text[i] != '\n' && lastSpaceIndex != -1) {
                temp_text[lastSpaceIndex] = '\n';
                i = lastSpaceIndex;
                currentLineWidth = currentLineWidth - lastSpaceLineWidth;
                lastSpaceIndex = -1;
            } else {
                if (temp_text[i] != '\n') {
                    memmove(&temp_text[i + 1], &temp_text[i], strlen(&temp_text[i]) + 1);
                    temp_text[i] = '\n';
                }
                currentLineWidth = charWidth; // Commencer la nouvelle ligne avec le caractère courant
            }
            currentLine++;
        }

        if (currentLine > maxLines) {
            temp_text[i] = '\0';
            break;
        }
    }

    strcpy(text, temp_text);
}
