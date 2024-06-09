// ImpulseManager.h
#ifndef IMPULSE_H
#define IMPULSE_H

// Structure Impulse
typedef struct Impulse {
    float magnitude;
    float direction;
    float duration;
    float timeElapsed;
} Impulse;

// Structure ImpulseManager
typedef struct ImpulseManager {
    Impulse** impulses;
    int max_impulses;
    int index;
} ImpulseManager;

// Fonctions pour l'Impulsion
Impulse* Impulse_Init(float magnitude, float direction, float duration);
void Impulse_Destroy(Impulse* impulse);

// Fonctions pour le gestionnaire d'impulsions
ImpulseManager* ImpulseManager_Init(int max_impulses);
void ImpulseManager_Destroy(ImpulseManager* manager);
void ImpulseManager_AddImpulse(ImpulseManager* manager, Impulse* impulse);

#endif // IMPULSE_H
