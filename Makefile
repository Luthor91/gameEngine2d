# Définition des variables
CC := gcc
SDL2 := -I/usr/include/SDL2
C_Graphics := $(wildcard ./Core/Graphics/src/*.c)
C_Physics := $(wildcard ./Core/Physics/src/*.c)
LDFLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf -lm

# Définition de la cible générique
physic:
	$(CC) $(SDL2) -o physic Examples/SDL2/physic.c $(C_Graphics) $(C_Physics) $(LDFLAGS) && ./physic

install: 
	sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev

tst:
	gcc -I/usr/include/SDL2 -o physic_test Examples/SDL2/physic_test.c Core/Graphics/src/animated_sprite.c Core/Graphics/src/sprite.c Core/Graphics/src/aspect.c Core/Graphics/src/window.c Core/Physics/src/rigidbody.c Core/Physics/src/transform.c Core/Physics/src/staticbody.c Core/Physics/src/characterbody.c Core/Physics/src/physics.c Core/Physics/src/acceleration.c Core/Physics/src/force.c Core/Physics/src/velocity.c Core/Physics/src/material.c Core/Physics/src/impulse.c Core/Physics/src/vector2.c -lSDL2 -lSDL2_image -lm && ./physic_test

window:
	gcc -I/usr/include/SDL2 -o window_test Examples/window.c Core/UI/src/window.c Core/Graphics/src/texture.c Core/Spatial/src/transform.c Core/Renderer/src/renderer.c Core/Font/src/label.c Core/Font/src/font.c Core/Graphics/src/color.c $(LDFLAGS) && ./window_test
