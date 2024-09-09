# Définition des variables
CC := gcc
OPTS := -fPIC -g
CFLAGS := $(OPTS) $(L_SDL2)
L_SDL2 := -I/usr/include/SDL2 
L_LDFLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm -Wl,--no-relax

# Windows-specific flags (non utilisés sur Linux)
W_SDL2 := -I"C:/msys64/mingw64/include/SDL2"
W_LDFLAGS := -L"C:/msys64/mingw64/lib" -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm 

# Détection des fichiers sources
Components := $(wildcard Core/Components/src/*.c)
Entities := $(wildcard Core/Entities/src/*.c)
Global := $(wildcard Core/Global/src/*.c)
Systems := $(wildcard Core/Systems/src/*.c)
Utils := $(wildcard Core/Utils/src/*.c)
Globals := $(wildcard Core/Globals/src/*.c)

AllFiles := $(Components) $(Entities) $(Global) $(Systems) $(Utils) $(Globals)

TD_Files := $(wildcard Example/TowerDefense/src/*.c)

# Cibles pour installation des dépendances
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

main:
	$(CC) $(CFLAGS) -o main Core/main.c $(AllFiles) $(L_LDFLAGS) && ./main

td:
	$(CC) $(CFLAGS) -o main Example/TowerDefense/main.c $(AllFiles) $(TD_Files) $(L_LDFLAGS) && ./main

# Nettoyage des fichiers compilés
##########
# CLEAN
##########

clean:
	rm -f *.o main