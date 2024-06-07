#ifndef STATICBODY_H
#define STATICBODY_H

#include "transform.h"
#include "physics.h"

typedef struct StaticBody {
    Physics* physics;
    Transform* transform;
} StaticBody;

typedef struct StaticBodyManager {
    StaticBody** staticBodies;
    int max_body;
    int index;
} StaticBodyManager;

#endif // STATICBODY_H
