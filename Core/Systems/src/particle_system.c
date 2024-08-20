#include "../include/particle_system.h"

ParticleEmitter emitters[MAX_EMITTERS];
int activeEmitterCount = 0;

// Fonction pour initialiser un émetteur de particules
void initParticleEmitter(const char* name, int particleCount, SDL_Texture* texture, int x, int y, float spreadness, float expansionRate) {
    // Recherche d'un émetteur inactif dans le tableau
    ParticleEmitter* emitter = NULL;
    for (int i = 0; i < MAX_EMITTERS; i++) {
        if (!emitters[i].active) {
            emitter = &emitters[i];
            break;
        }
    }
    if (emitter == NULL) {
        fprintf(stderr, "No available emitters.\n");
        return;
    }

    // Initialisation de l'émetteur
    strncpy(emitter->name, name, sizeof(emitter->name) - 1);
    emitter->particles = (Particle*)malloc(sizeof(Particle) * particleCount);
    if (emitter->particles == NULL) {
        fprintf(stderr, "Failed to allocate memory for particles.\n");
        return;
    }

    emitter->particleCount = particleCount;
    emitter->position.x = x;
    emitter->position.y = y;
    emitter->spreadness = spreadness;
    emitter->expansionRate = expansionRate;
    emitter->active = 0; // Activer directement lors de l'initialisation
    activeEmitterCount++;

    // Initialiser chaque particule
    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

    srand((unsigned int)time(NULL));

    for (int i = 0; i < particleCount; ++i) {
        Particle* particle = &emitter->particles[i];
        particle->texture = texture;
        particle->srcRect = (SDL_Rect){0, 0, textureWidth, textureHeight};

        // Position initiale de la particule
        particle->position.x = x;
        particle->position.y = y;

        // Calcul de la vélocité initiale en utilisant l'angle
        float angleDegrees = (float)(rand() % 360);
        float angleRadians = angleDegrees * (M_PI / 180.0f);
        float speed = 100.0f * expansionRate;
        particle->velocity.x = speed * cosf(angleRadians) * spreadness;
        particle->velocity.y = speed * sinf(angleRadians) * spreadness;

        particle->lifetime = MAX_PARTICLE_LIFETIME;
        particle->size = 1.0f;
        particle->active = 1;
    }
}

// Fonction pour mettre à jour les particules
void updateParticles(float deltaTime) {
    for (int i = 0; i < MAX_EMITTERS; i++) {
        if (!emitters[i].active) continue;

        ParticleEmitter* emitter = &emitters[i];

        int activeParticleCount = 0;

        // Mise à jour des particules
        for (int j = 0; j < emitter->particleCount; ++j) {
            Particle* particle = &emitter->particles[j];
            if (!particle->active) continue;

            // Mise à jour de la position en fonction de la vitesse
            particle->position.x += (int)(particle->velocity.x * deltaTime);
            particle->position.y += (int)(particle->velocity.y * deltaTime);

            // Réduction de la durée de vie
            particle->lifetime -= deltaTime;
            if (particle->lifetime <= 0) {
                // Marquer la particule comme inactive
                particle->active = 0;
            } else {
                // Conserver la particule active
                emitter->particles[activeParticleCount++] = *particle;
            }
        }

        // Réajuster le tableau des particules
        Particle* newParticles = (Particle*)realloc(emitter->particles, sizeof(Particle) * activeParticleCount);
        if (newParticles) {
            emitter->particles = newParticles;
            emitter->particleCount = activeParticleCount;
        } else {
            // En cas d'échec de réallocation, conserver l'ancien tableau
            // Afficher un message d'erreur et conserver l'ancien tableau
            fprintf(stderr, "Failed to reallocate memory for particles. Keeping old allocation.\n");
            // Note : L'ancien tableau est encore valide ici, donc pas besoin de libérer ou de manipuler l'ancien tableau.
        }

        // Si toutes les particules de l'émetteur sont inactives, désactiver l'émetteur
        if (activeParticleCount == 0) {
            emitter->active = 0;
            activeEmitterCount--;
        }
    }
}

ParticleEmitter* getEmitters() {
    return emitters;
}

int getActiveEmitterCount() {
    return activeEmitterCount;
}

void setEmitterPosition(const char* name, int x, int y) {
    for (int i = 0; i < MAX_EMITTERS; i++) {
        if (emitters[i].active && strcmp(emitters[i].name, name) == 0) {
            emitters[i].position.x = x;
            emitters[i].position.y = y;

            // Mettre à jour la position initiale de chaque particule en conséquence
            for (int j = 0; j < emitters[i].particleCount; j++) {
                Particle* particle = &emitters[i].particles[j];
                if (particle->active) {
                    particle->position.x = x;
                    particle->position.y = y;
                }
            }
            break;
        }
    }
}

// Fonction pour activer un émetteur par son nom
void activateEmitter(const char* name) {
    for (int i = 0; i < MAX_EMITTERS; i++) {
        if (strcmp(emitters[i].name, name) == 0) {
            if (!emitters[i].active) {
                emitters[i].active = 1;
                activeEmitterCount++;
            }
            break;
        }
    }
}

// Fonction pour désactiver un émetteur par son nom
void deactivateEmitter(const char* name) {
    for (int i = 0; i < MAX_EMITTERS; i++) {
        if (strcmp(emitters[i].name, name) == 0) {
            if (emitters[i].active) {
                emitters[i].active = 0;
                activeEmitterCount--;
            }
            break;
        }
    }
}

// Fonction pour libérer les ressources d'un émetteur de particules
void freeParticleEmitter(ParticleEmitter* emitter) {
    if (emitter->particles) {
        free(emitter->particles);
        emitter->particles = NULL;
    }
    emitter->particleCount = 0;
    emitter->active = 0;
    activeEmitterCount--;
}
