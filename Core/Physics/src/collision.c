#include "../include/collision.h"
#include <math.h>

int Collision_Check(Hitbox* hitboxA, Hitbox* hitboxB) {

    if (hitboxA->active == 0 || hitboxB->active == 0) { return 0; }

    // Position des centres des hitboxes
    Point2D* posA = Point2D_Init(
        hitboxA->transform->position->x + hitboxA->transform->size->width / 2, 
        hitboxA->transform->position->y + hitboxA->transform->size->height / 2
    );
    Point2D* posB = Point2D_Init(
        hitboxB->transform->position->x + hitboxB->transform->size->width / 2, 
        hitboxB->transform->position->y + hitboxB->transform->size->height / 2
    );

    // Si les deux hitboxes sont des cercles
    if (hitboxA->type == HITBOX_CIRCLE && hitboxB->type == HITBOX_CIRCLE) {
        float radiusA = fmax(hitboxA->transform->size->width, hitboxA->transform->size->height) / 2.0f;
        float radiusB = fmax(hitboxB->transform->size->width, hitboxB->transform->size->height) / 2.0f;
        float distX = posA->x - posB->x;
        float distY = posA->y - posB->y;
        float distance = sqrt(distX * distX + distY * distY);

        return distance < (radiusA + radiusB);
    }

    // Si les deux hitboxes sont des rectangles
    if (hitboxA->type == HITBOX_RECTANGLE && hitboxB->type == HITBOX_RECTANGLE) {
        return (fabs(posA->x - posB->x) < (hitboxA->transform->size->width / 2 + hitboxB->transform->size->width / 2)) &&
               (fabs(posA->y - posB->y) < (hitboxA->transform->size->height / 2 + hitboxB->transform->size->height / 2));
    }

    // Si une hitbox est un cercle et l'autre un rectangle
    if ((hitboxA->type == HITBOX_CIRCLE && hitboxB->type == HITBOX_RECTANGLE) ||
        (hitboxA->type == HITBOX_RECTANGLE && hitboxB->type == HITBOX_CIRCLE)) {
        // Pour simplifier, on traite toujours A comme le rectangle et B comme le cercle
        if (hitboxB->type == HITBOX_RECTANGLE) {
            Hitbox* temp = hitboxA;
            hitboxA = hitboxB;
            hitboxB = temp;
        }
        
        float closestX = fmax(hitboxA->transform->position->x, 
                              fmin(posB->x, hitboxA->transform->position->x + hitboxA->transform->size->width));
        float closestY = fmax(hitboxA->transform->position->y, 
                              fmin(posB->y, hitboxA->transform->position->y + hitboxA->transform->size->height));

        float distX = posB->x - closestX;
        float distY = posB->y - closestY;
        float distance = sqrt(distX * distX + distY * distY);

        float radiusB = fmax(hitboxB->transform->size->width, hitboxB->transform->size->height) / 2.0f;

        return distance < radiusB;
    }

    // Si les hitboxes sont des ovales
    if ((hitboxA->type == HITBOX_OVAL_X || hitboxA->type == HITBOX_OVAL_Y) ||
        (hitboxB->type == HITBOX_OVAL_X || hitboxB->type == HITBOX_OVAL_Y)) {

        // Calcul des distances normalisées
        float dx = (posA->x - posB->x) / (hitboxA->transform->size->width / 2 + hitboxB->transform->size->width / 2);
        float dy = (posA->y - posB->y) / (hitboxA->transform->size->height / 2 + hitboxB->transform->size->height / 2);
        float distance = dx * dx + dy * dy;

        return distance < 1.0f;
    }

    // Cas par défaut: pas de collision
    return 0;
}

void Collision_Handle(Physics* physics_body_1, Transform* transform_body_1, Hitbox* hitbox_body_1, 
                      Physics* physics_body_2, Transform* transform_body_2, Hitbox* hitbox_body_2) {

    if (Collision_Check(hitbox_body_1, hitbox_body_2)) {
        
        // Calcul de la normale de la collision basée sur les centres des hitboxes
        float normalX = (hitbox_body_2->transform->position->x + hitbox_body_2->transform->size->width / 2) - 
                        (hitbox_body_1->transform->position->x + hitbox_body_1->transform->size->width / 2);
        float normalY = (hitbox_body_2->transform->position->y + hitbox_body_2->transform->size->height / 2) - 
                        (hitbox_body_1->transform->position->y + hitbox_body_1->transform->size->height / 2);
        float normalLength = sqrt(normalX * normalX + normalY * normalY);
        normalX /= normalLength;
        normalY /= normalLength;

        // Vitesse relative entre les deux corps
        float relativeVelX = physics_body_2->velocity->x - physics_body_1->velocity->x;
        float relativeVelY = physics_body_2->velocity->y - physics_body_1->velocity->y;

        // Vitesse relative le long de la normale
        float velAlongNormal = relativeVelX * normalX + relativeVelY * normalY;

        // Ne pas résoudre si les objets s'éloignent
        if (velAlongNormal > 0) return;

        // Calcul du coefficient de restitution (bounciness)
        float e = fmin(physics_body_1->material->restitution_coefficient, physics_body_2->material->restitution_coefficient);

        // Calcul de l'impulsion scalaire
        float j = -(1 + e) * velAlongNormal;
        j /= (1 / physics_body_1->material->mass + 1 / physics_body_2->material->mass);

        // Calcul de l'impulsion vectorielle
        float impulseX = j * normalX;
        float impulseY = j * normalY;

        // Calcul de la magnitude et de la direction de l'impulsion
        float magnitude = sqrt(impulseX * impulseX + impulseY * impulseY);
        float direction1 = atan2(-impulseY, -impulseX); // Impulsion pour le corps 1 (opposé à la direction de l'impulsion)
        float direction2 = atan2(impulseY, impulseX);   // Impulsion pour le corps 2 (direction de l'impulsion)
        float duration = 0.1f; // Durée de l'impulsion, peut être ajustée

        // Initialiser et ajouter les impulsions aux deux corps
        Impulse* impulse1 = Impulse_Init(magnitude, direction1, duration);
        ImpulseManager_Add(physics_body_1->impulses, impulse1);
        
        Impulse* impulse2 = Impulse_Init(magnitude, direction2, duration);
        ImpulseManager_Add(physics_body_2->impulses, impulse2);

        // Déactivation temporaire de la hitbox
        /*
        hitbox_body_1->active = 0;
        Timer* timer = Timer_Init(1, Hitbox_SetActive, &hitbox_body_1->active, 0);
        TimerManager_Add(TIMER_MANAGER, timer);
        */
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
                        physics_bodies->cb_manager->bodies[i]->hitbox,
                        physics_bodies->cb_manager->bodies[j]->physics,
                        physics_bodies->cb_manager->bodies[j]->transform,
                        physics_bodies->cb_manager->bodies[j]->hitbox
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
                        physics_bodies->rb_manager->bodies[i]->hitbox,
                        physics_bodies->rb_manager->bodies[j]->physics,
                        physics_bodies->rb_manager->bodies[j]->transform,
                        physics_bodies->rb_manager->bodies[j]->hitbox
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
                        physics_bodies->sb_manager->bodies[i]->hitbox,
                        physics_bodies->sb_manager->bodies[j]->physics,
                        physics_bodies->sb_manager->bodies[j]->transform,
                        physics_bodies->sb_manager->bodies[j]->hitbox
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
                        physics_bodies->cb_manager->bodies[i]->hitbox,
                        physics_bodies->rb_manager->bodies[j]->physics,
                        physics_bodies->rb_manager->bodies[j]->transform,
                        physics_bodies->rb_manager->bodies[j]->hitbox
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
                        physics_bodies->cb_manager->bodies[i]->hitbox,
                        physics_bodies->sb_manager->bodies[j]->physics,
                        physics_bodies->sb_manager->bodies[j]->transform,
                        physics_bodies->sb_manager->bodies[j]->hitbox
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
                        physics_bodies->rb_manager->bodies[i]->hitbox,
                        physics_bodies->sb_manager->bodies[j]->physics,
                        physics_bodies->sb_manager->bodies[j]->transform,
                        physics_bodies->sb_manager->bodies[j]->hitbox
                    );
                }
            }
        }
    }

