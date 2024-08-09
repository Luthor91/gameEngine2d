#ifndef HITBOX_H
#define HITBOX_H

#include <stdlib.h>
#include "../../Spatial/include/transform.h"  // Assure-toi que Transform est défini ici ou dans un fichier séparé

// Définition des types de hitbox
typedef enum HitboxType {
    HITBOX_RECTANGLE,
    HITBOX_CIRCLE,
    HITBOX_OVAL_X,  // Oval avec largeur > hauteur
    HITBOX_OVAL_Y   // Oval avec hauteur > largeur
} HitboxType;

// Définition de la structure Hitbox
typedef struct Hitbox {
    Transform* transform;  // Position, taille, rotation, etc.
    HitboxType type;       // Type de la hitbox (Rectangle, Cercle, etc.)
    int active;            // 1 si la hitbox est active, 0 sinon
} Hitbox;

// Fonction d'initialisation
Hitbox* Hitbox_Init(Transform* transform, HitboxType type);

void Hitbox_SetActive(void* flag_hitbox);

void Hitbox_SetInactive(void* flag_hitbox);

#endif // HITBOX_H
