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

void clean_param_name(char* param_name);

void CheckTextFit(Font* font, char* text, int maxWidth, int maxHeight);

int is_percentage(const char* str);

int parse_percentage(const char* str, int max_value);

int parse_dimension(const char* str, int default_value, int base_size);

#endif // STRING_H
