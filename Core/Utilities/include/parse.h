#ifndef PARSE_H
#define PARSE_H

#include "../../Utilities/include/global.h"
#include "../../Graphics/include/color.h"
#include "../../Spatial/include/size2d.h"

void Parse_CleanParamName(char* param_name);

int Parse_Expression(const char* expr, int object_value, const char* param_name);

int Parse_Color(Color* color, const char* str);

void apply_operator(char operator, int* result, int current_value);

void handle_percentage(const char* param_name, int percent, int object_value, int* current_value, int window_width, int window_height);

#endif // PARSE_H
