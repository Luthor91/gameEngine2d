#include "../include/data_component.h"

// Table des composants de données pour les entités (ici un tableau statique pour la simplicité)
static DataComponent dataComponents[MAX_ENTITIES] = { [0 ... MAX_ENTITIES-1] = DATA_COMPONENT_DEFAULT };

// Fonction pour obtenir le DataComponent d'une entité
DataComponent* getDataComponent(Entity entity) {
    if (entity < MAX_ENTITIES) {
        return &dataComponents[entity];
    }
    return NULL; // Retourne NULL si l'entité est invalide
}

// Fonction pour ajouter un DataComponent à une entité
void addDataComponent(Entity entity, DataComponent data) {
    if (entity < MAX_ENTITIES) {
        dataComponents[entity] = data;
        hasDatas[entity] = true;
    }
}

// Pour récupérer la valeur d'un DataType spécifique pour une entité donnée
float getDataValue(Entity entity, DataType type) {
    if (entity < MAX_ENTITIES && type < DATA_MAX) {
        DataComponent* component = getDataComponent(entity);
        if (component != NULL) {
            return component->values[type];
        }
    }
    return -1;
}

void setDataValue(Entity entity, DataType type, float value) {
    if (entity < MAX_ENTITIES && type < DATA_MAX) {
        DataComponent* component = getDataComponent(entity);
        if (component != NULL) {
            component->values[type] = value;
        }
    }
}

bool hasDataValue(Entity entity, DataType type) {
    if (entity < MAX_ENTITIES && type < DATA_MAX) {
        DataComponent* component = getDataComponent(entity);
        if (component != NULL) {
            // Vérifie si la valeur pour le type de donnée est différente de 0
            return component->values[type] != 0;
        }
    }
    return false;
}
