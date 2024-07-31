#include "../include/staticbody.h"

StaticBody* StaticBody_Init(Transform* transform, Physics* physics) {
    StaticBody* body = (StaticBody*)malloc(sizeof(StaticBody));
    if (!body) return NULL;

    body->physics = physics;
    body->transform = transform;

    return body;
}

void StaticBody_Destroy(StaticBody* body) {
    if (body) {
        free(body->physics);
        free(body->transform);
        free(body);
    }
}

StaticBodyManager* StaticBodyManager_Init(int max_body) {
    StaticBodyManager* manager = (StaticBodyManager*)malloc(sizeof(StaticBodyManager));
    if (!manager) return NULL;

    manager->staticBodies = (StaticBody**)malloc(sizeof(StaticBody*) * max_body);
    if (!manager->staticBodies) {
        free(manager);
        return NULL;
    }

    manager->max_body = max_body;
    manager->index = 0;

    return manager;
}

void StaticBodyManager_AddBody(StaticBodyManager* manager, StaticBody* body) {
    if (manager->index < manager->max_body) {
        manager->staticBodies[manager->index++] = body;
    }
}

void StaticBodyManager_Destroy(StaticBodyManager* manager) {
    if (manager) {
        for (int i = 0; i < manager->index; ++i) {
            StaticBody_Destroy(manager->staticBodies[i]);
        }
        free(manager->staticBodies);
        free(manager);
    }
}