#ifndef HITBOX_H
#define HITBOX_H

#include "../../Entities/include/entity.h"  // Assurez-vous d'inclure le fichier core.h pour Entity, etc.

// Structure définissant un composant Hitbox
typedef struct HitboxComponent {
    float x, y;  // Décalage de la hitbox par rapport à la position de l'entité
    float width, height;     // Largeur et hauteur de la hitbox
} HitboxComponent;

// Fonction pour ajouter une hitbox à une entité
void addHitboxComponent(Entity entity, HitboxComponent hitbox);

// Fonction pour obtenir une hitbox d'une entité
HitboxComponent* getHitboxComponent(Entity entity);

void updateHitbox(Entity entity);

#endif