#include "../include/font.h"

int Font_Start() {

    if(!TTF_WasInit() && TTF_Init() == -1) {
        printf("Font_Start: %s\n", TTF_GetError());
        return 0;
    }
    return 1;
}

Font* Font_SetSize(Font* font, int size) {
    if (!font || size <= 0) return NULL;

    TTF_CloseFont(font->sdl_font);
    font->sdl_font = TTF_OpenFont(font->path, size);
    if (!font->sdl_font) {
        printf("Font_SetSize : Échec de la modification de la taille du texte: %s\n", TTF_GetError());
    }

    return font;
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