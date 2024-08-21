#ifndef DATA_COMPONENT_H
#define DATA_COMPONENT_H

#include <stdlib.h>
#include "../../Entities/include/entity.h"

// Initialisation par défaut du DataComponent (par exemple, toutes les valeurs à 0)
#define DATA_COMPONENT_DEFAULT { {0} }

// Définition des types de données possibles
typedef enum DataType {
    DATA_HEALTH,
    DATA_MAX_HEALTH,
    DATA_ARMOR,
    DATA_ATTACK,
    DATA_SPEED,
    DATA_PASSIVE,
    DATA_LEVEL,
    DATA_SCORE,
    DATA_DIFFICULTY,
    DATA_CAPABLE,
    DATA_AGRO,
    DATA_COUNT_SHOOT,
    // Ajouter d'autres types de données ici

    DATA_MAX // Cette valeur indique le nombre total d'éléments dans l'enum
} DataType;
//static int difficulty = 0;
//static int enemies_killed = 0;
//static int bullet_count = 0;
//static bool can_shoot = true;
// Structure pour un DataComponent
typedef struct DataComponent {
    float values[DATA_MAX]; // Tableau pour stocker les différentes valeurs des données
} DataComponent;

// Fonction pour ajouter un DataComponent à une entité
void addDataComponent(Entity entity, DataComponent data);

// Fonction pour obtenir un pointeur vers le DataComponent d'une entité
DataComponent* getDataComponent(Entity entity);

float getDataValue(Entity entity, DataType type);

void setDataValue(Entity entity, DataType type, float value);

bool hasDataValue(Entity entity, DataType type);

#endif // DATA_COMPONENT_H
