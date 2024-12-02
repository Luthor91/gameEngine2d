# Définition des variables
CC := gcc
# A voir pour rajouter -fPIC et -Wall
OPTS :=  -g -m64
CFLAGS := $(OPTS) $(L_SDL2)
L_SDL2 := -I/usr/include/SDL2 
L_LDFLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm -mcmodel=medium -Wl,--no-relax 

# Windows-specific flags (non utilisés sur Linux)
W_SDL2 := -I"C:/msys64/mingw64/include/SDL2"
W_LDFLAGS := -L"C:/msys64/mingw64/lib" -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm 

# Détection des fichiers sources
Globals := $(wildcard Core/Globals/src/*.c)
Engine := $(wildcard Core/Engine/src/*.c)
Utils := $(wildcard Core/Utils/src/*.c)
Systems := $(wildcard Core/Systems/src/*.c)
Entities := $(wildcard Core/Entities/src/*.c)
Components := $(wildcard Core/Components/src/*.c)

AllFiles := $(Globals) $(Engine) $(Utils) $(Systems) $(Entities) $(Components)

TD_Files := $(wildcard Example/TowerDefense/src/*.c)

##########
# INSTALL
##########

linstall: 
	sudo apt update
	sudo apt install -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev gdb 

winstall:
	choco upgrade chocolatey
	choco install -y manaplus

ainstall:
	sudo pacman -Syu
	sudo pacman -S sdl2 sdl2_image sdl2_ttf sdl2_mixer gdb

##########
# BUILD
##########

test:
	$(CC) $(CFLAGS) -o main Core/main.c $(AllFiles) $(L_LDFLAGS) && ./main

td:
	$(CC) $(CFLAGS) -o main Example/TowerDefense/main.c $(AllFiles) $(TD_Files) $(L_LDFLAGS) && ./main

rpg:
	$(CC) $(CFLAGS) -o main Example/RPG/main.c $(AllFiles) $(TD_Files) $(L_LDFLAGS) && ./main

# Nettoyage des fichiers compilés
##########
# CLEAN
##########

clean:
	rm -f *.o main