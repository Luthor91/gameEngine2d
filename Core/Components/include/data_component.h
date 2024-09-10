#ifndef DATA_COMPONENT_H
#define DATA_COMPONENT_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../../Entities/include/entity.h"

// Génération de l'énumération DataType avec le préprocesseur
typedef enum DataType {
    #define X(name) name,
        DATA_TYPE_LIST
    #undef X
    DATA_MAX // Cette valeur indique le nombre total d'éléments dans l'enum
} DataType;

// Structure pour un DataComponent
typedef struct DataComponent {
    float values[DATA_MAX + 128]; // Inclure de l'espace pour les types dynamiques
} DataComponent;

// Définition de la structure pour les types de données dynamiques
typedef struct {
    char name[32];
    int index;
} DynamicDataType;

// Fonctions pour gérer les DataComponent
void addDataComponent(Entity entity, DataComponent data);
DataComponent* getDataComponent(Entity entity);
float getDataValue(Entity entity, int type);
void setDataValue(Entity entity, int type, float value);
bool hasDataValue(Entity entity, int type);

// Fonction pour ajouter un type de données dynamique
int addDataType(const char* typeName);
int getDataType(const char* typeName);

#endif // DATA_COMPONENT_H