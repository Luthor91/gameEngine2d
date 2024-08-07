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

void StaticBodyManager_Add(StaticBodyManager* manager, ...) {
    va_list args;
    va_start(args, manager);

    int num_bodies = 0;
    StaticBody* body;

    // Compter les arguments variadiques jusqu'à rencontrer NULL
    while ((body = va_arg(args, StaticBody*)) != NULL) {
        num_bodies++;
    }
    va_end(args);
    va_start(args, manager); // Réinitialiser va_list pour réutilisation

    for (int i = 0; i < num_bodies; i++) {
        
        body = va_arg(args, StaticBody*);

        if (body == NULL) {
            fprintf(stderr, "RigidBodyManager_AddBodies: RigidBody at index %d is NULL\n", i);
            break;
        }

        if (manager->index >= manager->max_body) {
            fprintf(stderr, "RigidBodyManager_AddBodies: Maximum number of rigid bodies reached\n");
            break;
        }

        manager->staticBodies[manager->index++] = body;
    }

    va_end(args);
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