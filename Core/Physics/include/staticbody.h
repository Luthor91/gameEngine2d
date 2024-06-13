#ifndef STATICBODY_H
#define STATICBODY_H

#include "../../Spatial/include/transform.h"
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

// Initialisation des fonctions
StaticBody* StaticBody_Init(Transform* transform, Physics* physics);
void StaticBody_Destroy(StaticBody* body);

StaticBodyManager* StaticBodyManager_Init(int max_body);
void StaticBodyManager_AddBody(StaticBodyManager* manager, StaticBody* body);
void StaticBodyManager_Destroy(StaticBodyManager* manager);

#endif // STATICBODY_H
