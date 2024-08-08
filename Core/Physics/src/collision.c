#include "../include/collision.h"
#include <math.h>

int Collision_Check(Transform* transA, Transform* transB) {
    Point2D* posA = Point2D_Init(transA->position->x + transA->size->width / 2, transA->position->y + transA->size->height / 2);
    Point2D* posB = Point2D_Init(transB->position->x + transB->size->width / 2, transB->position->y + transB->size->height / 2);
    
    float radiusA = fmax(transA->size->width, transA->size->height) / 2.0f;
    float radiusB = fmax(transB->size->width, transB->size->height) / 2.0f;

    float distX = posA->x - posB->x;
    float distY = posA->y - posB->y;
    float distance = sqrt(distX * distX + distY * distY);

    return distance < (radiusA + radiusB);
}

void Collision_Handle(Physics* physics_body_1, Transform* transform_body_1, Physics* physics_body_2, Transform* transform_body_2) {

    if (Collision_Check(transform_body_1, transform_body_2)) {
        
        // Calcul de la normale de la collision
        float normalX = transform_body_2->position->x - transform_body_1->position->x;
        float normalY = transform_body_2->position->y - transform_body_1->position->y;
        float normalLength = sqrt(normalX * normalX + normalY * normalY);
        normalX /= normalLength;
        normalY /= normalLength;

        // Vitesse relative
        float relativeVelX = physics_body_2->velocity->x - physics_body_1->velocity->x;
        float relativeVelY = physics_body_2->velocity->y - physics_body_1->velocity->y;

        // Vitesse relative le long de la normale
        float velAlongNormal = relativeVelX * normalX + relativeVelY * normalY;

        // Ne pas résoudre si les objets s'éloignent
        if (velAlongNormal > 0) return;

        // Calcul du coefficient de restitution
        float e = fmin(physics_body_1->material->restitution_coefficient, physics_body_2->material->restitution_coefficient);

        // Calcul de l'impulsion scalaire
        float j = -(1 + e) * velAlongNormal;
        j /= (1 / physics_body_1->material->mass + 1 / physics_body_2->material->mass);

        // Calcul de l'impulsion vectorielle
        float impulseX = j * normalX;
        float impulseY = j * normalY;

        // Calcul de la magnitude et de la direction de l'impulsion
        float magnitude = sqrt(impulseX * impulseX + impulseY * impulseY);
        float direction = atan2(impulseY, impulseX);
        float duration = 0.1f; // Durée de l'impulsion, peut être ajustée

        // Initialiser et ajouter les impulsions aux deux corps
        Impulse* impulse1 = Impulse_Init(magnitude, direction + PI, duration);
        ImpulseManager_Add(physics_body_1->impulses, impulse1);
        
        Impulse* impulse2 = Impulse_Init(magnitude, direction, duration);
        ImpulseManager_Add(physics_body_2->impulses, impulse2);

        printf("Collision_Handle: magnitude:%lf\n", magnitude);
    }
}

// Fonction pour gérer les collisions entre tous les corps physiques
void Collision_HandleAll(PhysicsBodies* physics_bodies) {
    size_t i, j;

    // Vérifier si les gestionnaires sont NULL
    if (!physics_bodies) return;

    // Gérer les collisions entre CharacterBodies
    if (physics_bodies->cb_manager && physics_bodies->cb_manager->index > 0) {
        for (i = 0; i < physics_bodies->cb_manager->max_body; ++i) {
            for (j = i + 1; j < physics_bodies->cb_manager->max_body; ++j) {
                if (!physics_bodies->cb_manager->bodies[i] || !physics_bodies->cb_manager->bodies[j]) {
                    continue;
                }
                Collision_Handle(
                    physics_bodies->cb_manager->bodies[i]->physics,
                    physics_bodies->cb_manager->bodies[i]->transform,
                    physics_bodies->cb_manager->bodies[j]->physics,
                    physics_bodies->cb_manager->bodies[j]->transform
                );
            }
        }
    }

    // Gérer les collisions entre RigidBodies
    if (physics_bodies->rb_manager && physics_bodies->rb_manager->index > 0) {
        for (i = 0; i < physics_bodies->rb_manager->max_body; ++i) {
            for (j = i + 1; j < physics_bodies->rb_manager->max_body; ++j) {
                if (!physics_bodies->rb_manager->bodies[i] || !physics_bodies->rb_manager->bodies[j]) {
                    continue;
                }
                Collision_Handle(
                    physics_bodies->rb_manager->bodies[i]->physics,
                    physics_bodies->rb_manager->bodies[i]->transform,
                    physics_bodies->rb_manager->bodies[j]->physics,
                    physics_bodies->rb_manager->bodies[j]->transform
                );
            }
        }
    }

    // Gérer les collisions entre StaticBodies
    if (physics_bodies->sb_manager && physics_bodies->sb_manager->index > 0) {
        for (i = 0; i < physics_bodies->sb_manager->max_body; ++i) {
            for (j = i + 1; j < physics_bodies->sb_manager->max_body; ++j) {
                if (!physics_bodies->sb_manager->bodies[i] || !physics_bodies->sb_manager->bodies[j]) {
                    continue;
                }
                Collision_Handle(
                    physics_bodies->sb_manager->bodies[i]->physics,
                    physics_bodies->sb_manager->bodies[i]->transform,
                    physics_bodies->sb_manager->bodies[j]->physics,
                    physics_bodies->sb_manager->bodies[j]->transform
                );
            }
        }
    }

    // Gérer les collisions entre CharacterBodies et RigidBodies
    if (physics_bodies->cb_manager && physics_bodies->rb_manager && physics_bodies->cb_manager->index > 0 && physics_bodies->rb_manager->index > 0) {
        for (i = 0; i < physics_bodies->cb_manager->max_body; ++i) {
            for (j = 0; j < physics_bodies->rb_manager->max_body; ++j) {
                if (!physics_bodies->cb_manager->bodies[i] || !physics_bodies->rb_manager->bodies[j]) {
                    continue;
                }
                Collision_Handle(
                    physics_bodies->cb_manager->bodies[i]->physics,
                    physics_bodies->cb_manager->bodies[i]->transform,
                    physics_bodies->rb_manager->bodies[j]->physics,
                    physics_bodies->rb_manager->bodies[j]->transform
                );
            }
        }
    }

    // Gérer les collisions entre CharacterBodies et StaticBodies
    if (physics_bodies->cb_manager && physics_bodies->sb_manager && physics_bodies->cb_manager->index > 0 && physics_bodies->sb_manager->index > 0) {
        for (i = 0; i < physics_bodies->cb_manager->max_body; ++i) {
            for (j = 0; j < physics_bodies->sb_manager->max_body; ++j) {
                if (!physics_bodies->cb_manager->bodies[i] || !physics_bodies->sb_manager->bodies[j]) {
                    continue;
                }
                Collision_Handle(
                    physics_bodies->cb_manager->bodies[i]->physics,
                    physics_bodies->cb_manager->bodies[i]->transform,
                    physics_bodies->sb_manager->bodies[j]->physics,
                    physics_bodies->sb_manager->bodies[j]->transform
                );
            }
        }
    }

    // Gérer les collisions entre RigidBodies et StaticBodies
    if (physics_bodies->rb_manager && physics_bodies->sb_manager && physics_bodies->rb_manager->index > 0 && physics_bodies->sb_manager->index > 0) {
        for (i = 0; i < physics_bodies->rb_manager->max_body; ++i) {
            for (j = 0; j < physics_bodies->sb_manager->max_body; ++j) {
                if (!physics_bodies->rb_manager->bodies[i] || !physics_bodies->sb_manager->bodies[j]) {
                    continue;
                }
                Collision_Handle(
                    physics_bodies->rb_manager->bodies[i]->physics,
                    physics_bodies->rb_manager->bodies[i]->transform,
                    physics_bodies->sb_manager->bodies[j]->physics,
                    physics_bodies->sb_manager->bodies[j]->transform
                );
            }
        }
    }
}
