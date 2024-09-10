#include "../include/size_component.h"

static SizeComponent sizeComponents[MAX_ENTITIES] = {0};

// Fonction pour ajouter un composant Size à une entité
void addSizeComponent(Entity entity, SizeComponent size) {
    if (entity >= 0 && entity < MAX_ENTITIES) {
        sizeComponents[entity] = size;
        hasSize[entity] = true;
    } else {
        printf("Error: Invalid entity ID %d\n", entity);
    }
}

// Fonction pour obtenir un pointeur sur le composant Size d'une entité
SizeComponent* getSizeComponent(Entity entity) {
    if (entity >= 0 && entity < MAX_ENTITIES && hasSize[entity]) {
        return &sizeComponents[entity];
    } else {
        return NULL;
    }
}

// Fonction pour définir la taille d'une entité existante
void setSize(Entity entity, float width, float height) {
    SizeComponent* size = getSizeComponent(entity);
    if (size) {
        size->width = width;
        size->height = height;
    }
}

// Fonction pour obtenir la largeur d'une entité
float getWidth(Entity entity) {
    SizeComponent* size = getSizeComponent(entity);
    return size ? size->width : 0.0f;
}

// Fonction pour obtenir la hauteur d'une entité
float getHeight(Entity entity) {
    SizeComponent* size = getSizeComponent(entity);
    return size ? size->height : 0.0f;
}
