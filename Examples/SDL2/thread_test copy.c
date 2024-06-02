// gcc -I/usr/include/SDL2 -o animation_test Examples/SDL2/animation_test.c Core/Graphics/src/sprite.c Core/Graphics/src/tilemap.c Core/Graphics/src/transform.c Core/Graphics/src/window.c Core/Graphics/src/animation.c -lSDL2 -lSDL2_image -lSDL_thread -lm && ./animation_test


#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>

#include "../../Core/Graphics/include/sprite.h"
#include "../../Core/Graphics/include/tilemap.h"
#include "../../Core/Graphics/include/transform.h"
#include "../../Core/Graphics/include/animation.h"
#include "../../Core/Graphics/include/window.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32
#define NUM_SPRITES 8
#define ANIMATION_SPEED 100

//The threads that will be used
SDL_Thread *threadA = NULL;
SDL_Thread *threadB = NULL;

//The protective semaphore
SDL_sem *videoLock = NULL;

void show_surface( int x, int y, SDL_Surface* source )
{
    //Lock
    SDL_SemWait( videoLock );
    
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, NULL, screen, &offset );
    
    //Update the screen
    SDL_Flip( screen );

    //Unlock
    SDL_SemPost( videoLock );
}

int blitter_a( void *data )
{
    //Y offset
    int y = 10;
    
    //Go through the surface
    for( int b = 0; b < 5; b++ )
    {
        //Wait
        SDL_Delay( 200 );
    
        //Show surface
        show_surface( ( ( SCREEN_WIDTH / 2 ) - text[ b ]->w ) / 2, y, text[ b ] );
        
        //Move down
        y += 100;
    }
    
    return 0;
}

int blitter_b( void *data )
{
    //Y offset
    int y = 10;
    
    //Go through the surface
    for( int b = 0; b < 5; b++ )
    {
        //Wait
        SDL_Delay( 200 );
    
        //Show surface
        show_surface( ( SCREEN_WIDTH / 2 ) + ( ( ( SCREEN_WIDTH / 2 ) - text[ b ]->w ) / 2 ), y, text[ b ] );
        
        //Move down
        y += 100;
    }
    
    return 0;
}

int init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return 0;    
    }
    
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return 0;    
    }
    
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return 0;    
    }
    
    //Create the semaphore
    videoLock = SDL_CreateSemaphore( 1 );
    
    //Set the window caption
    SDL_WM_SetCaption( "Testing Threads", NULL );
    
    //If everything initialized fine
    return 1;
}

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Main: %s\n", SDL_GetError());
        return 1;
    }





    return 0;
}

