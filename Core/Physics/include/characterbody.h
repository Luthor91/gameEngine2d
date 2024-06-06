#ifndef CHARACTERBODY_H
#define CHARACTERBODY_H

#include "transform.h"
#include "physics.h"

typedef struct CharacterBody {
    Physics* physics;
    Transform* transform;
} CharacterBody;

typedef struct CharacterBodyManager {
    CharacterBody* characterBodies;
    int max_body;
    int index;
} CharacterBodyManager;

void UpdateCharacterBody(CharacterBody* body, float deltaTime);

#endif // CHARACTERBODY_H
