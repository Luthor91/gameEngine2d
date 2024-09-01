# Définition des variables
CC := gcc
OPTS := -fPIC
L_SDL2 := -I/usr/include/SDL2 
L_LDFLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm 

# Windows-specific flags
W_SDL2 := -I"C:/msys64/mingw64/include/SDL2" 
W_LDFLAGS := -L"C:/msys64/mingw64/lib" -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

SYMBOL := $(OPTS) -g -o

Components := $(wildcard Core/Components/src/*.c)
Entities := $(wildcard Core/Entities/src/*.c)
Global := $(wildcard Core/GLobal/src/*.c)
Systems := $(wildcard Core/Systems/src/*.c)
Utils := $(wildcard Core/Utils/src/*.c)
Globals := $(wildcard Core/Globals/src/*.c)

AllFiles := $(Components) $(Entities) $(Global) $(Systems) $(Utils) $(Globals)

TD_Files := $(wildcard Example/TowerDefense/src/*.c)

##########
# INSTALL
##########

linstall: 
	sudo apt update
	sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev gdb 

winstall:
	choco upgrade chocolatey
	choco install -y manaplus

ainstall:
	sudo pacman -Syu
	sudo pacman -S sdl2 sdl2_image sdl2_ttf libsdl2-mixer-dev gdb

lt_main:
	$(CC) $(L_SDL2) $(SYMBOL) main Core/main.c $(AllFiles) $(L_LDFLAGS) && ./main

l_td:
	$(CC) $(L_SDL2) $(SYMBOL) main Example/TowerDefense/main.c $(AllFiles) $(TD_Files) $(L_LDFLAGS) && ./main
