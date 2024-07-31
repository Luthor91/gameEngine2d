#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdlib.h>

// Valeur de la constante PI utilisée pour les calculs trigonométriques.
#define PI 3.14159265358979323846

// Définition des directions principales en radians
#define DIRECTION_NORTH       (3 * M_PI / 2) ///< Direction Nord, en radians.
#define DIRECTION_NORTHEAST   (7 * M_PI / 4) ///< Direction Nord-Est, en radians.
#define DIRECTION_EAST        0.0f ///< Direction Est, en radians.
#define DIRECTION_SOUTHEAST   (M_PI / 4) ///< Direction Sud-Est, en radians.
#define DIRECTION_SOUTH       (M_PI / 2) ///< Direction Sud, en radians.
#define DIRECTION_SOUTHWEST   (3 * M_PI / 4) ///< Direction Sud-Ouest, en radians.
#define DIRECTION_WEST        M_PI ///< Direction Ouest, en radians.
#define DIRECTION_NORTHWEST   (5 * M_PI / 4) ///< Direction Nord-Ouest, en radians.
#include "acceleration.h"
#include "force.h"
#include "impulse.h"
#include "velocity.h"
#include "material.h"

/**
 * Représente les propriétés physiques d'un objet, telles que l'accélération, les forces, les impulsions, la vitesse et le matériau.
 */
typedef struct Physics {
    Acceleration* acceleration; ///< Accélération appliquée à l'objet.
    ForceManager* forces; ///< Gestionnaire des forces appliquées à l'objet.
    ImpulseManager* impulses; ///< Gestionnaire des impulsions appliquées à l'objet.
    Velocity* velocity; ///< Vitesse actuelle de l'objet.
    Material* material; ///< Matériau de l'objet, utilisé pour les calculs de friction et de restitution.
    int isGrounded; ///< Indicateur si l'objet est au sol (1 pour vrai, 0 pour faux).
} Physics;

/**
 * Initialise un objet Physics avec les propriétés physiques spécifiées.
 *
 * @param acceleration Pointeur vers l'objet Acceleration associé à l'objet physique.
 * @param force_manager Pointeur vers le gestionnaire des forces appliquées à l'objet.
 * @param impulse_manager Pointeur vers le gestionnaire des impulsions appliquées à l'objet.
 * @param velocity Pointeur vers l'objet Velocity associé à l'objet physique.
 * @param material Pointeur vers l'objet Material représentant les propriétés du matériau de l'objet.
 * @return Pointeur vers la nouvelle instance de Physics initialisée.
 */
Physics* Physics_Init(Acceleration* acceleration, ForceManager* force_manager, ImpulseManager* impulse_manager, Velocity* velocity, Material* material);

#endif // PHYSICS_H
