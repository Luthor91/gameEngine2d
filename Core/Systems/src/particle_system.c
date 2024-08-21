#include "../include/particle_system.h"

ParticleEmitter emitters[MAX_EMITTERS];
int activeEmitterCount = 0;

// Fonction pour initialiser un émetteur de particules
void initParticleEmitter(const char* name, int particleCount, SDL_Texture* texture, int x, int y, float spreadness, float expansionRate) {
    ParticleEmitter* emitter = NULL;
    for (int i = 0; i < MAX_EMITTERS; i++) {
        if (!emitters[i].initialized) {
            emitter = &emitters[i];
            break;
        }
    }
    if (emitter == NULL) {
        fprintf(stderr, "No available emitters.\n");
        return;
    }

    strncpy(emitter->name, name, sizeof(emitter->name) - 1);
    emitter->particleCount = particleCount > MAX_PARTICLES ? MAX_PARTICLES : particleCount;
    emitter->position.x = x;
    emitter->position.y = y;
    emitter->spreadness = spreadness;
    emitter->expansionRate = expansionRate;
    emitter->active = 0;
    emitter->initialized = 1; // Marquer comme initialisé
    activeEmitterCount++;

    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

    for (int i = 0; i < MAX_PARTICLES; i++) {
        Particle* particle = &emitter->particles[i];
        if (i < emitter->particleCount) {
            particle->texture = texture;
            particle->srcRect = (SDL_Rect){0, 0, textureWidth, textureHeight};

            particle->position.x = x;
            particle->position.y = y;

            float angleDegrees = (float)(rand() % 360);
            float angleRadians = angleDegrees * (M_PI / 180.0f);
            float speed = 100.0f * expansionRate;
            particle->velocity.x = speed * cosf(angleRadians) * spreadness;
            particle->velocity.y = speed * sinf(angleRadians) * spreadness;

            particle->lifetime = MAX_PARTICLE_LIFETIME;
            particle->current_lifetime = MAX_PARTICLE_LIFETIME; // Initialisation de current_lifetime
            particle->size = 1.0f;
            particle->active = 1;
            
        } else {
            particle->active = 0;
        }
    }
}


// Fonction pour mettre à jour les particules
void updateParticles(float deltaTime) {
    for (int i = 0; i < MAX_EMITTERS; i++) {
        if (!emitters[i].active || !emitters[i].initialized) continue;

        ParticleEmitter* emitter = &emitters[i];
        int allParticlesInactive = 1;

        // Mise à jour des particules
        for (int j = 0; j < emitter->particleCount; j++) {
            Particle* particle = &emitter->particles[j];
            if (!particle->active) continue;

            // Mise à jour de la position en fonction de la vitesse
            particle->position.x += (int)(particle->velocity.x * deltaTime);
            particle->position.y += (int)(particle->velocity.y * deltaTime);

            // Réduction de la durée de vie restante
            particle->current_lifetime -= deltaTime;
            if (particle->current_lifetime <= 0) {
                // Marquer la particule comme inactive
                particle->active = 0;
            }

            allParticlesInactive = 0; // Il y a au moins une particule active
        }

        // Si toutes les particules de l'émetteur sont inactives, désactiver l'émetteur
        if (allParticlesInactive) {
            emitter->active = 0;
            activeEmitterCount--;
            if (strcmp(emitter->name, "") == 0) {
                emitter->initialized = 0;
            }
            
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
        if (strcmp(emitters[i].name, name) == 0) {
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
            ParticleEmitter* emitter = &emitters[i];
            if (!emitter->active) {
                emitter->active = 1;
                activeEmitterCount++;

                // Activer les particules en fonction de particleCount
                for (int j = 0; j < emitter->particleCount; j++) {
                    Particle* particle = &emitter->particles[j];
                    particle->active = 1; // Marquer la particule comme active
                    particle->current_lifetime = particle->lifetime;
                }
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
        //free(emitter->particles);
    }
    emitter->particleCount = 0;
    emitter->active = 0;
    activeEmitterCount--;
}

// Fonction pour copier un émetteur de particules sans nom
void instanciateParticleEmitter(const char* sourceName) {
    ParticleEmitter* sourceEmitter = NULL;
    ParticleEmitter* targetEmitter = NULL;

    // Trouver l'émetteur source
    for (int i = 0; i < MAX_EMITTERS; i++) {
        if (strcmp(emitters[i].name, sourceName) == 0) {
            sourceEmitter = &emitters[i];
            break;
        }
    }

    if (sourceEmitter == NULL) {
        fprintf(stderr, "Source emitter not found or is inactive.\n");
        return;
    }

    // Trouver un émetteur non initialisé pour la copie
    for (int i = 0; i < MAX_EMITTERS; i++) {
        if (!emitters[i].initialized) {
            targetEmitter = &emitters[i];
            break;
        }
    }

    if (targetEmitter == NULL) {
        fprintf(stderr, "No available emitters for copying.\n");
        return;
    }

    // Copier les données de l'émetteur source vers l'émetteur cible
    targetEmitter->name[0] = '\0';
    targetEmitter->particleCount = sourceEmitter->particleCount;
    targetEmitter->position = sourceEmitter->position;
    targetEmitter->spreadness = sourceEmitter->spreadness;
    targetEmitter->expansionRate = sourceEmitter->expansionRate;

    // Copier les particules
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (i < targetEmitter->particleCount) {
            targetEmitter->particles[i] = sourceEmitter->particles[i]; // Copier les données de particule
        } else {
            targetEmitter->particles[i].active = 0; // Marquer les particules excédentaires comme inactives
        }
    }

    // Activer le nouvel émetteur
    targetEmitter->active = 1;
    targetEmitter->initialized = 1;
    activeEmitterCount++;
}
