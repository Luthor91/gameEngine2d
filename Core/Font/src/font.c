#include "../include/font.h"

int Font_Start() {

    if(!TTF_WasInit() && TTF_Init() == -1) {
        printf("Font_Start: %s\n", TTF_GetError());
        return 0;
    }
    return 1;
}

Font* Font_Init(Color* color, char* path, int size) {

    if (path == NULL ) {
        path = "Assets/Fonts/Open_Sans/OpenSans_Condensed-Bold.ttf";
    }

    if (color == NULL) {
        color = &COLOR_BLACK;
    }
    
    Font* font = malloc(sizeof(Font));

    TTF_Font* ttf_font = TTF_OpenFont(path, size);
    if (!ttf_font) {
        printf("Font_Init: %s\n", TTF_GetError());
        TTF_CloseFont(ttf_font);
        free(font);
        return NULL;
    }

    font->color = color;
    font->sdl_font = ttf_font;
    font->size = size;
    font->path = path;

    return font;

}