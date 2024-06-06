# Définition des variables
CC := gcc
SDL2 := -I/usr/include/SDL2
C_Graphics := $(wildcard ./Core/Graphics/src/*.c)
C_Physics := $(wildcard ./Core/Physics/src/*.c)
LDFLAGS := -lSDL2 -lSDL2_image -lm

# Définition de la cible générique
physic:
	$(CC) $(SDL2) -o physic Examples/SDL2/physic.c $(C_Graphics) $(C_Physics) $(LDFLAGS) && ./physic

tst:
	gcc -I/usr/include/SDL2 -o physic_test Examples/SDL2/physic_test.c Core/Graphics/src/animated_sprite.c Core/Graphics/src/sprite.c Core/Graphics/src/aspect.c Core/Graphics/src/window.c Core/Physics/src/rigidbody.c Core/Physics/src/transform.c Core/Physics/src/staticbody.c Core/Physics/src/characterbody.c Core/Physics/src/physics.c Core/Physics/src/acceleration.c Core/Physics/src/force.c Core/Physics/src/velocity.c Core/Physics/src/vector2.c -lSDL2 -lSDL2_image -lm && ./physic_test