#include "../include/particle_system.h"

ParticleEmitter activeEmitters[MAX_EMITTERS];
int activeEmitterCount = 0;

// Fonction pour initialiser un émetteur de particules
void initParticleEmitter(ParticleEmitter* emitter, int particleCount, SDL_Texture* texture, int x, int y, float expansionRate) {
    // Libérer les ressources précédentes si elles existent
    if (emitter->particles != NULL) {
        free(emitter->particles);
        emitter->particles = NULL;
    }

    // Allouer de la mémoire pour les particules
    emitter->particles = (Particle*)malloc(sizeof(Particle) * particleCount);
    if (emitter->particles == NULL) {
        fprintf(stderr, "Failed to allocate memory for particles.\n");
        return;
    }
    
    emitter->particleCount = particleCount;
    emitter->active = 1;
    emitter->position.x = x;
    emitter->position.y = y;
    emitter->expansionRate = expansionRate;  // Taux d'expansion des particules

    // Obtenir la taille de la texture
    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

    // Initialiser le générateur de nombres aléatoires
    static int randomSeedInitialized = 0;
    if (!randomSeedInitialized) {
        srand((unsigned int)time(NULL));
        randomSeedInitialized = 1;
    }

    // Initialiser chaque particule
    for (int i = 0; i < particleCount; ++i) {
        Particle* particle = &emitter->particles[i];
        particle->texture = texture;
        particle->srcRect = (SDL_Rect){0, 0, textureWidth, textureHeight};

        particle->position.x = x;
        particle->position.y = y;

        // Calculer l'angle aléatoire en degrés puis le convertir en radians
        float angleDegrees = (float)(rand() % 360);
        float angleRadians = angleDegrees * (M_PI / 180.0f);
        
        // Calculer la vitesse initiale en fonction du taux d'expansion
        float speed = 100.0f * emitter->expansionRate;
        particle->velocity.x = speed * cosf(angleRadians);
        particle->velocity.y = speed * sinf(angleRadians);

        particle->lifetime = 1.5f;  // Durée de vie initiale
        particle->size = 1.0f;     // Taille initiale
        particle->active = 1;      // Activée par défaut pour l'affichage
    }
}

// Fonction pour mettre à jour les particules d'un émetteur
void updateParticles(ParticleEmitter* emitter, float deltaTime) {
    if (!emitter->active) return;

    for (int i = 0; i < emitter->particleCount; ++i) {
        Particle* particle = &emitter->particles[i];
        if (!particle->active) continue;

        // Mise à jour de la position en fonction de la vitesse
        particle->position.x += particle->velocity.x * deltaTime;
        particle->position.y += particle->velocity.y * deltaTime;

        // Réduction de la durée de vie
        particle->lifetime -= deltaTime;
        if (particle->lifetime <= 0) {
            printf("Particle n°%d disabled\n", i);
            particle->active = 0; // Désactive la particule si sa durée de vie est écoulée
        }
    }
}

// Fonction pour libérer les ressources d'un émetteur de particules
void freeParticleEmitter(ParticleEmitter* emitter) {
    free(emitter->particles);
    emitter->particles = NULL;
    emitter->particleCount = 0;
    emitter->active = 0;
}
