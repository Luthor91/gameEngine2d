#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_EMITTERS 64
#define MAX_PARTICLE_LIFETIME 1.0f  // Durée de vie maximale d'une particule
#define M_PI           3.14159265358979323846

// Structure de la particule
typedef struct Particle {
    SDL_Texture* texture;
    SDL_Rect srcRect;
    struct {
        int x;  // Coordonnée X de la position
        int y;  // Coordonnée Y de la position
    } position;
    struct {
        float x;  // Composante X de la vitesse
        float y;  // Composante Y de la vitesse
    } velocity;
    float lifetime;
    float size;
    int active;
} Particle;

// Structure de l'émetteur de particules
typedef struct ParticleEmitter {
    char name[32];  // Nom de l'émetteur
    Particle* particles;
    int particleCount;
    struct {
        int x;  // Coordonnée X de la position
        int y;  // Coordonnée Y de la position
    } position;
    float spreadness;  // Écartement des particules autour du point d'origine
    float expansionRate;  // Vitesse à laquelle les particules s'éloignent
    int active;
} ParticleEmitter;

// Déclarations des fonctions
void initParticleEmitter(const char* name, int particleCount, SDL_Texture* texture, int x, int y, float spreadness, float expansionRate);
void updateParticles(float deltaTime);
ParticleEmitter* getEmitters();
int getActiveEmitterCount();
void setEmitterPosition(const char* name, int x, int y);
void activateEmitter(const char* name);
void deactivateEmitter(const char* name);
void freeParticleEmitter(ParticleEmitter* emitter);

#endif  // PARTICLE_SYSTEM_H