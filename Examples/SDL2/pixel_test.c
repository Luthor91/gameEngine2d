#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char* argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Initialisation de SDL_image
    if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) {
        printf("Erreur lors de l'initialisation de SDL_image : %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Inverser les couleurs", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Chargement de l'image JPEG
    SDL_Surface* imageSurface = IMG_Load("Assets/Image/background1.jpg");
    if (!imageSurface) {
        printf("Erreur lors du chargement de l'image : %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Création d'une texture à partir de l'image
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (!texture) {
        printf("Erreur lors de la création de la texture : %s\n", SDL_GetError());
        SDL_FreeSurface(imageSurface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Libération de la mémoire de la surface de l'image
    SDL_FreeSurface(imageSurface);

    // Affichage de la texture sur le renderer
    SDL_Rect rect = {0, 0, imageSurface->w, imageSurface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);

    // Récupération des pixels de la texture
    Uint32 format;
    int access;
    void* pixels;
    int pitch;
    SDL_QueryTexture(texture, &format, &access, NULL, &pitch);

    // Verrouiller la texture pour obtenir un pointeur vers les données de pixels
    if (SDL_LockTexture(texture, NULL, &pixels, &pitch) < 0) {
        printf("Erreur lors du verrouillage de la texture : %s\n", SDL_GetError());
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Création d'une surface à partir des pixels récupérés
    SDL_Surface* pixelSurface = SDL_CreateRGBSurfaceFrom(pixels, imageSurface->w, imageSurface->h, SDL_BITSPERPIXEL(format), pitch,
                                                        0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    if (!pixelSurface) {
        printf("Erreur lors de la création de la surface à partir des pixels : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    // Affichage de la surface sur le renderer
    rect = (SDL_Rect){0, 0, imageSurface->w, imageSurface->h};
    texture = SDL_CreateTextureFromSurface(renderer, pixelSurface);
    if (!texture) {
        printf("Erreur lors de la création de la texture à partir de la surface : %s\n", SDL_GetError());
        SDL_FreeSurface(pixelSurface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);

    // Libération de la mémoire
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(pixelSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}