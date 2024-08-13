#ifndef HITBOX_H
#define HITBOX_H

#include "../../Entities/include/entity.h"  // Assurez-vous d'inclure le fichier core.h pour Entity, etc.

// Structure définissant un composant Hitbox
typedef struct {
    float offsetX, offsetY;  // Décalage de la hitbox par rapport à la position de l'entité
    float width, height;     // Largeur et hauteur de la hitbox
} HitboxComponent;

// Déclaration du tableau des composants Hitbox et des vérifications de leur existence
static HitboxComponent hitboxComponents[MAX_ENTITIES];

// Fonction pour ajouter une hitbox à une entité
void addHitboxComponent(Entity entity, float offsetX, float offsetY, float width, float height);

// Fonction pour obtenir une hitbox d'une entité
HitboxComponent* getHitboxComponent(Entity entity);

// Fonction pour vérifier les collisions entre deux entités
bool checkCollision(Entity entity1, Entity entity2);

#endif // HITBOX_H
