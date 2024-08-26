#include "../include/data_component.h"
#include <string.h>
#include <stdio.h>

// Table des composants de données pour les entités (ici un tableau statique pour la simplicité)
static DataComponent dataComponents[MAX_ENTITIES] = { [0 ... MAX_ENTITIES-1] = DATA_COMPONENT_DEFAULT };

// Tableau pour les types de données dynamiques
static DynamicDataType dynamicTypes[DATA_MAX_DYNAMIC_TYPE];
static int dynamicTypeCount = 0;

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
    }
}

// Fonction pour récupérer la valeur d'un DataType spécifique pour une entité donnée
float getDataValue(Entity entity, int type) {
    if (entity < MAX_ENTITIES) {
        DataComponent* component = getDataComponent(entity);
        if (component != NULL) {
            if (type < DATA_MAX) {
                return component->values[type];
            } else {
                // Index pour les types dynamiques
                int dynamicIndex = type - DATA_MAX;
                if (dynamicIndex < dynamicTypeCount) {
                    return component->values[DATA_MAX + dynamicIndex];
                }
            }
        }
    }
    return DATA_INVALID_VALUE;
}

// Fonction pour définir une valeur pour un DataType spécifique pour une entité donnée
void setDataValue(Entity entity, int type, float value) {
    if (entity < MAX_ENTITIES) {
        DataComponent* component = getDataComponent(entity);
        if (component != NULL) {
            if (type < DATA_MAX) {
                component->values[type] = value;
            } else {
                // Index pour les types dynamiques
                int dynamicIndex = type - DATA_MAX;
                if (dynamicIndex < dynamicTypeCount) {
                    component->values[DATA_MAX + dynamicIndex] = value;
                }
            }
        }

        
    }
}

// Fonction pour vérifier si un DataType spécifique pour une entité donnée a une valeur différente de 0
bool hasDataValue(Entity entity, int type) {
    if (entity < MAX_ENTITIES) {
        DataComponent* component = getDataComponent(entity);
        if (component != NULL) {
            if (type < DATA_MAX) {
                return component->values[type] != 0;
            } else {
                // Index pour les types dynamiques
                int dynamicIndex = type - DATA_MAX;
                if (dynamicIndex < dynamicTypeCount) {
                    return component->values[DATA_MAX + dynamicIndex] != 0;
                }
            }
        }
    }
    return false;
}

// Fonction pour ajouter un type de données dynamique
int addDataType(const char* typeName) {
    if (dynamicTypeCount >= DATA_MAX_DYNAMIC_TYPE) {
        return DATA_INVALID_VALUE; // Erreur : nombre maximum de types atteint
    }

    // Vérifier si le type existe déjà
    for (int i = 0; i < dynamicTypeCount; ++i) {
        if (strcmp(dynamicTypes[i].name, typeName) == 0) {
            return DATA_INVALID_VALUE; // Retourne l'index existant
        }
    }

    // Ajouter le nouveau type
    strncpy(dynamicTypes[dynamicTypeCount].name, typeName, sizeof(dynamicTypes[dynamicTypeCount].name) - 1);
    dynamicTypes[dynamicTypeCount].index = DATA_MAX + dynamicTypeCount; // Assigne un nouvel index
    return dynamicTypes[dynamicTypeCount++].index;
}

// Fonction pour ajouter un type de données dynamique
int getDataType(const char* typeName) {
    if (dynamicTypeCount >= DATA_MAX_DYNAMIC_TYPE) {
        return DATA_INVALID_VALUE; // Erreur : nombre maximum de types atteint
    }

    // Vérifier si le type existe déjà
    for (int i = 0; i < dynamicTypeCount; ++i) {
        if (strcmp(dynamicTypes[i].name, typeName) == 0) {
            return dynamicTypes[i].index; // Retourne l'index existant
        }
    }
    return DATA_INVALID_VALUE;
}