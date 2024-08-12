#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "../../Entities/include/entity.h"

#define DEFAULT_TRANSFORM {0.0f, 0.0f, 1.0f, 1.0f, 0.0f}

typedef struct TransformComponent {
    float x, y; // Position de l'entité
    float scaleX, scaleY; // Échelle de l'entité
    float rotation; // Rotation de l'entité en degrés
} TransformComponent;

TransformComponent* getTransformComponent(Entity entity);
void addTransformComponent(Entity entity, TransformComponent transform);

#endif
