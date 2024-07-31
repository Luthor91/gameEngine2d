#ifndef CHARACTERBODY_H
#define CHARACTERBODY_H

#include "../../Spatial/include/transform.h"
#include "physics.h"

// Structure représentant un corps de personnage.
// Contient des données de physique et de transformation pour le personnage.
typedef struct CharacterBody {
    Physics* physics; ///< Pointeur vers la structure de physique associée au personnage.
    Transform* transform; ///< Pointeur vers la structure de transformation associée au personnage.
} CharacterBody;

// Structure pour gérer plusieurs corps de personnage.
// Contient un tableau de pointeurs vers les corps de personnage, 
// ainsi que des informations sur la capacité et l'index courant.
typedef struct CharacterBodyManager {
    CharacterBody** characterBodies; ///< Tableau de pointeurs vers les corps de personnage.
    int max_body; ///< Nombre maximum de corps de personnage pouvant être gérés.
    int index; ///< Index courant dans le tableau de corps de personnage.
} CharacterBodyManager;

#endif // CHARACTERBODY_H
