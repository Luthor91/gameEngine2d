args = `arg="$(filter-out $@,$(MAKECMDGOALS))" && echo $${arg:-${1}}`

# Définition des variables
CC := gcc
SDL2 := -I/usr/include/SDL2
LDFLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf -lm
SYMBOL := -g -o

Animation := $(wildcard Core/Animation/src/*.c)
Events := $(wildcard Core/Events/src/*.c)
Font := $(wildcard Core/Font/src/*.c)
Graphics := $(wildcard Core/Graphics/src/*.c)
Physics := $(wildcard Core/Physics/src/*.c)
Renderer := $(wildcard Core/Renderer/src/*.c)
Shape := $(wildcard Core/Shape/src/*.c)
Spatial := $(wildcard Core/Spatial/src/*.c)
Tilemap := $(wildcard Core/Tilemap/src/*.c)
UI := $(wildcard Core/UI/src/*.c)
Utilities := $(wildcard Core/Utilities/src/*.c)

AllFiles := $(Animation) $(Events) $(Font) $(Graphics) $(Physics) $(Renderer) $(Shape) $(Spatial) $(Tilemap) $(UI) $(Utilities)


install: 
	sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev gdb

# Cible pour compiler et exécuter un exemple spécifique
t_window:
	$(CC) $(SDL2) $(SYMBOL) test_window Examples/window.c $(AllFiles) $(LDFLAGS) && ./test_window

t_animation:
	$(CC) $(SDL2) $(SYMBOL) test_animation Examples/animation.c $(AllFiles) $(LDFLAGS) && ./test_animation

t_sprites:
	$(CC) $(SDL2) $(SYMBOL) test_sprites Examples/sprites.c $(AllFiles) $(LDFLAGS) && ./test_sprites
