#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdlib.h>

#define PI 3.14159265358979323846

#include "acceleration.h"
#include "force.h"
#include "velocity.h"
#include "material.h"

typedef struct Physics {
    Acceleration* acceleration;
    ForceManager* forces;
    Velocity* velocity;
    Material* material;
    int isGrounded;
} Physics;

Physics* Physics_Init(Acceleration* acceleration, ForceManager* force_manager, Velocity* velocity, Material* material);

#endif // PHYSICS_H
