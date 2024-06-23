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