// ImpulseManager.h
#ifndef IMPULSE_H
#define IMPULSE_H

#define DIRECTION_NORTH       (3 * PI / 2)
#define DIRECTION_NORTHEAST   (7 * PI / 4)
#define DIRECTION_EAST        0.0f
#define DIRECTION_SOUTHEAST   (PI / 4)
#define DIRECTION_SOUTH       (PI / 2)
#define DIRECTION_SOUTHWEST   (3 * PI / 4)
#define DIRECTION_WEST        PI
#define DIRECTION_NORTHWEST   (5 * PI / 4)

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
