#include "../include/collision.h"
#include <math.h>

int Collision_Check(Point2D* posA, Point2D* posB, float radiusA, float radiusB) {
    float distX = posA->x - posB->x;
    float distY = posA->y - posB->y;
    float distance = sqrt(distX * distX + distY * distY);

    return distance < (radiusA + radiusB);
}

void Collision_Handle(Physics* physics_body_1, Transform* transform_body_1, Physics* physics_body_2, Transform* transform_body_2) {
    if (Collision_Check(transform_body_1->position, transform_body_2->position, 1.0f, 1.0f)) {
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
        ImpulseManager_AddImpulse(physics_body_1->impulses, impulse1);

        Impulse* impulse2 = Impulse_Init(magnitude, direction, duration);
        ImpulseManager_AddImpulse(physics_body_2->impulses, impulse2);
    }
}
