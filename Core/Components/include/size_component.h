#ifndef SIZE_COMPONENT_H
#define SIZE_COMPONENT_H

#include "../../Entities/include/entity.h"
#include <stdio.h>

// Définition du composant Size
typedef struct {
    float width;
    float height;
} SizeComponent;

// Fonction pour ajouter un composant Size à une entité
void addSizeComponent(Entity entity, SizeComponent size);

// Fonction pour obtenir un pointeur sur le composant Size d'une entité
SizeComponent* getSizeComponent(Entity entity);

// Fonction pour définir la taille d'une entité existante
void setSize(Entity entity, float width, float height);

// Fonction pour obtenir la largeur d'une entité
float getWidth(Entity entity);

// Fonction pour obtenir la hauteur d'une entité
float getHeight(Entity entity);

#endif // SIZE_COMPONENT_H
