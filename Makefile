# Définition des variables
CC := gcc
SDL2 := -I/usr/include/SDL2
C_Graphics := $(wildcard ./Core/Graphics/src/*.c)
C_Physics := $(wildcard ./Core/Physics/src/*.c)
LDFLAGS := -lSDL2 -lSDL2_image -lm

# Définition de la cible générique
$(target):
	$(CC) $(SDL2) -o $(target) Examples/SDL2/$(target).c $(C_Graphics) $(C_Physics) $(LDFLAGS) && ./$(target)
