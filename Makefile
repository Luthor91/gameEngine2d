# Définition des variables
CC := gcc
L_SDL2 := -I/usr/include/SDL2
L_LDFLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf -lm
W_LDFLAGS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lX11 -lm

SYMBOL := -g -o

Components := $(wildcard Core/Components/src/*.c)
Entities := $(wildcard Core/Entities/src/*.c)
Global := $(wildcard Core/GLobal/src/*.c)
Systems := $(wildcard Core/Systems/src/*.c)
Utils := $(wildcard Core/Utils/src/*.c)

AllFiles := $(Components) $(Entities) $(Global) $(Systems) $(Utils)


linstall: 
	sudo apt update
	sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev gdb

winstall:
	choco upgrade chocolatey
	choco install -y mingw --version 12.2.0.03042023 --allow-downgrade
	choco install -y manaplus

ainstall:
	sudo pacman -Syu
	sudo pacman -S sdl2 sdl2_image sdl2_ttf gdb

##############################################
#
#		LINUX
#
##############################################

lt_main:
	$(CC) $(L_SDL2) $(SYMBOL) main Core/main.c $(AllFiles) $(L_LDFLAGS) && ./main

lt_window:
	$(CC) $(L_SDL2) $(SYMBOL) test_window Examples/window.c $(AllFiles) $(L_LDFLAGS) && ./test_window

lt_animation:
	$(CC) $(L_SDL2) $(SYMBOL) test_animation Examples/animation.c $(AllFiles) $(L_LDFLAGS) && ./test_animation

lt_sprites:
	$(CC) $(L_SDL2) $(SYMBOL) test_sprites Examples/sprites.c $(AllFiles) $(L_LDFLAGS) && ./test_sprites

lt_interface:
	$(CC) $(L_SDL2) $(SYMBOL) test_interface Examples/interface.c $(AllFiles) $(L_LDFLAGS) && ./test_interface

lt_physics:
	$(CC) $(L_SDL2) $(SYMBOL) test_physics Examples/physics.c $(AllFiles) $(L_LDFLAGS) && ./test_physics

lt_events:
	$(CC) $(L_SDL2) $(SYMBOL) test_events Examples/events.c $(AllFiles) $(L_LDFLAGS) && ./test_events

lt_clicker:
	$(CC) $(L_SDL2) $(SYMBOL) project_clicker ProjectClicker/main.c $(AllFiles) $(L_LDFLAGS) && ./project_clicker

##############################################
#
#		WINDOWS
#
##############################################

wt_window:
	$(CC) $(W_SDL2) $(SYMBOL) test_window Examples/window.c $(AllFiles) $(W_LDFLAGS) && ./test_window

wt_animation:
	$(CC) $(W_SDL2) $(SYMBOL) test_animation Examples/animation.c $(AllFiles) $(W_LDFLAGS) && ./test_animation

wt_sprites:
	$(CC) $(W_SDL2) $(SYMBOL) test_sprites Examples/sprites.c $(AllFiles) $(L_WDFLAGS) && ./test_sprites