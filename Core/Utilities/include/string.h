#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "global.h"
#include "../../Font/include/font.h"

/**
 * @brief Concatène deux chaînes de caractères.
 * 
 * @param str1 La première chaîne de caractères.
 * @param str2 La deuxième chaîne de caractères.
 * @return char* Une nouvelle chaîne de caractères résultant de la concaténation de str1 et str2. 
 *         L'appelant est responsable de libérer cette mémoire.
 */
char* String_Concat(const char* str1, const char* str2);

void CheckTextFit(Font* font, char* text, int maxWidth, int maxHeight);

#endif // STRING_H
