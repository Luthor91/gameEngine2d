#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdlib.h>

#include "acceleration.h"
#include "force.h"
#include "velocity.h"
#include "material.h"

typedef struct Physics {
    Acceleration* acceleration;
    Force* force;
    Velocity* velocity;
    Material* material;
    int isGrounded;
} Physics;

Physics* Physics_Init(Acceleration* acceleration, Force* force, Velocity* velocity, Material* material);

#endif // PHYSICS_H
