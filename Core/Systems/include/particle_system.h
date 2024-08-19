#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_EMITTERS 100 

// Structure pour représenter une particule
typedef struct Particle {
    SDL_Texture* texture;       // Texture de la particule
    SDL_Rect srcRect;           // Rectangle source pour le rendu de la texture
    struct {
        int x;  // Coordonnée X de la position
        int y;  // Coordonnée Y de la position
    } position;
    struct {
        float x;  // Composante X de la vitesse
        float y;  // Composante Y de la vitesse
    } velocity;
    float lifetime;             // Durée de vie de la particule en secondes
    float size;                 // Taille de la particule
    int active;                 // Indicateur si la particule est active
} Particle;

// Structure pour gérer un émetteur de particules
typedef struct ParticleEmitter {
    Particle* particles;        // Tableau de particules
    int particleCount;          // Nombre de particules gérées par l'émetteur
    struct {
        int x;  // Coordonnée X de la position
        int y;  // Coordonnée Y de la position
    } position;
    float expansionRate;
    int active;                 // Indicateur si l'émetteur est actif
} ParticleEmitter;

extern ParticleEmitter activeEmitters[MAX_EMITTERS];
extern int activeEmitterCount;

// Fonction pour initialiser un émetteur de particules
void initParticleEmitter(ParticleEmitter* emitter, int particleCount, SDL_Texture* texture, int x, int y, float expansionRate) ;

// Fonction pour mettre à jour les particules d'un émetteur
void updateParticles(ParticleEmitter* emitter, float deltaTime);

// Fonction pour libérer les ressources d'un émetteur de particules
void freeParticleEmitter(ParticleEmitter* emitter);

#endif // PARTICLE_SYSTEM_H
