#include "../include/string_utils.h"

bool isAsciiString(const char* str) {
    while (*str) {
        if (!isascii((unsigned char)*str)) {  // Vérifie si chaque caractère est ASCII
            return false;
        }
        str++;
    }
    return true;
}