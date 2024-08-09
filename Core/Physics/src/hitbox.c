#include "../include/hitbox.h"

// Fonction d'initialisation de la hitbox
Hitbox* Hitbox_Init(Transform* transform, HitboxType type) {
    Hitbox* hitbox = (Hitbox*)malloc(sizeof(Hitbox));
    if (!hitbox) {
        return NULL;  // Échec de l'allocation
    }
    if (!type) {
        type = HITBOX_RECTANGLE;
    }

    hitbox->transform = transform;
    hitbox->type = type;
    hitbox->active = 1;  // Par défaut, la hitbox est active

    return hitbox;
}

void Hitbox_SetActive(void* flag_hitbox) {
    if (flag_hitbox != NULL) {
        *((int*)flag_hitbox) = 1;
    }
}

void Hitbox_SetInactive(void* flag_hitbox) {
    if (flag_hitbox != NULL) {
        *((int*)flag_hitbox) = 0;
    }
}

