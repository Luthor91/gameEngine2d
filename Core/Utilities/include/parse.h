#ifndef PARSE_H
#define PARSE_H

#include "../../Utilities/include/global.h"
#include "../../Graphics/include/color.h"

void Parse_CleanParamName(char* param_name);

int Parse_Expression(const char* expr, int object_value);

int Parse_Color(Color* color, const char* str);

#endif // PARSE_H
