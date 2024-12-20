#include "../include/collision_system.h"
#include "../include/event_system.h"

// Fonction pour initialiser le système de collision (si nécessaire)
void initCollisionSystem() {
    // Initialisation spécifique si nécessaire
}

CollisionData* CollisionData_Init(Entity entity1, Entity entity2) {
    CollisionData* collider = (CollisionData*)malloc(sizeof(CollisionData));
    if (collider == NULL) {
        printf("Memory allocation failed for collider1\n");
        return NULL;
    }

    // Associer les entités
    collider->entity1 = entity1;
    collider->entity2 = entity2;

    // Obtenir les centres des entités
    PositionComponent* position_entity1 = getCenterPosition(entity1);
    PositionComponent* position_entity2 = getCenterPosition(entity2);

    // Calculer la position de la collision (point médian)
    collider->position_x = (position_entity1->x + position_entity2->x) / 2.0f;
    collider->position_y = (position_entity1->y + position_entity2->y) / 2.0f;

    // Calculer la direction (vecteur de pos1 vers pos2)
    collider->direction_x = position_entity2->x - position_entity1->x;
    collider->direction_y = position_entity2->y - position_entity1->y;

    // Normaliser le vecteur direction
    float length = sqrt(collider->direction_x * collider->direction_x + collider->direction_y * collider->direction_y);
    if (length > 0) {
        collider->direction_x /= length;
        collider->direction_y /= length;
    }

    return collider;
}


// Fonction pour libérer les données de collision
void CollisionData_Free(CollisionData* colliderData) {
    if (colliderData != NULL) {
        free(colliderData);
        colliderData = NULL;
    }
}

// Fonction pour mettre à jour le système de collision
void updateCollisionSystem() {
    // Obtenez l'index pour le type d'événement de collision
    EventType EVENT_COLLIDE = getEventType("EVENT_COLLIDE");

    // Boucle pour chaque paire unique d'entités
    for (Entity entity1 = 0; entity1 < getEntityCount(); ++entity1) {
        if (!hasHitbox[entity1] || !hasPosition[entity1] || !isEntityEnabled(entity1)) continue;

        for (Entity entity2 = entity1 + 1; entity2 < getEntityCount(); ++entity2) {
            if (!hasHitbox[entity2] || !hasPosition[entity2] || !isEntityEnabled(entity2)) continue;

            if (checkCollision(entity1, entity2)) {
                printf("Collision between : %s : %s\n", getFirstTag(entity1), getFirstTag(entity2));
                
                // Initialisez les données de collision pour les deux entités
                CollisionData* colliderData = CollisionData_Init(entity1, entity2);

                if (colliderData == NULL) {
                    printf("Failed to allocate memory for collision data.\n");
                    continue;
                }

                // Créez l'événement de collision
                Event event;
                event.type = EVENT_COLLIDE;
                event.data = (CollisionData*)malloc(sizeof(CollisionData));
                if (event.data != NULL) {
                    memcpy(event.data, colliderData, sizeof(CollisionData)); // Copier les données de colliderData
                } else {
                    free(event.data);
                    event.data = NULL;
                    continue;
                }
                strncpy(event.name, "collision", sizeof(event.name) - 1);
                event.name[sizeof(event.name) - 1] = '\0';

                // Émettez l'événement
                emitEvent(event);

            }
        }
    }
}

// Fonction pour vérifier la collision entre deux entités
bool checkCollision(Entity entity1, Entity entity2) {
    HitboxComponent* hitbox1 = getHitboxComponent(entity1);
    HitboxComponent* hitbox2 = getHitboxComponent(entity2);

    PositionComponent* pos1 = getPositionComponent(entity1);
    PositionComponent* pos2 = getPositionComponent(entity2);

    if (!hitbox1 || !hitbox2 || !pos1 || !pos2) {
        printf("Error: Missing components for entities %ld or %ld\n", entity1, entity2);
        return false;
    }

    if (!hitbox1->is_active || !hitbox2->is_active) {
        return false;
    }

    // Calculer les positions des hitboxes
    float leftA = pos1->x + hitbox1->x;
    float rightA = leftA + hitbox1->width;
    float topA = pos1->y + hitbox1->y;
    float bottomA = topA + hitbox1->height;

    float leftB = pos2->x + hitbox2->x;
    float rightB = leftB + hitbox2->width;
    float topB = pos2->y + hitbox2->y;
    float bottomB = topB + hitbox2->height;

    // Vérifier les chevauchements des rectangles (AABB collision detection)
    if (rightA <= leftB || leftA >= rightB || bottomA <= topB || topA >= bottomB) {
        return false;
    }

    return true;
}

bool checkCollisionTags(Event event, const char* tag1, const char* tag2) {
    // Vérification que les données de l'événement ne sont pas nulles
    if (event.data == NULL) return false;
    
    // Extraction des données de collision de l'événement
    CollisionData* collision_data = (CollisionData*)event.data;
    if (collision_data == NULL) return false;

    // Récupération des entités impliquées dans la collision
    Entity entity1 = collision_data->entity1;
    Entity entity2 = collision_data->entity2;

    // Vérification que les entités sont valides et activées
    if (!isEntityEnabled(entity1) || !isEntityEnabled(entity2)) return false;

    // Si tag1 est NULL, ne pas vérifier le tag1 pour entity1
    if (tag1 == NULL) {
        // Si tag2 est NULL, aucune vérification supplémentaire n'est nécessaire, retournez true
        if (tag2 == NULL) return true;
        // Vérifiez seulement si entity2 possède tag2
        return hasTag(entity2, tag2);
    }

    // Si tag2 est NULL, ne vérifiez que tag1 pour entity1
    if (tag2 == NULL) {
        return hasTag(entity1, tag1);
    }

    // Vérifiez que les entités ont les tags spécifiés
    return hasTag(entity1, tag1) && hasTag(entity2, tag2);
}
