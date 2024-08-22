#include "../include/tag_component.h"
#include "../../Systems/include/event_system.h"

static TagComponent tagComponents[MAX_ENTITIES];

static int findTagIndex(TagComponent* tagComp, const char* tag) {
    for (int i = 0; i < tagComp->tagCount; ++i) {
        if (strcmp(tagComp->tags[i], tag) == 0) {
            return i;
        }
    }
    return -1;
}

// Ajouter un TagComponent à une entité
void addTagComponent(Entity entity, TagComponent tagComponent) {
    tagComponents[entity] = tagComponent;
    hasTags[entity] = true;
}

// Obtenir le TagComponent d'une entité
TagComponent* getTagComponent(Entity entity) {
    return &tagComponents[entity];
}

// Fonction pour obtenir le premier tag d'une entité
const char* getFirstTag(Entity entity) {
    if (entity < 0 || entity >= MAX_ENTITIES) {
        return NULL;  // Vérifier si l'entité est valide
    }

    TagComponent* tagComponent = &tagComponents[entity];

    if (tagComponent->tagCount == 0) {
        return NULL;  // Retourner NULL si l'entité n'a pas de tags
    }

    return tagComponent->tags[0];  // Retourner le premier tag
}

// Ajouter un tag à une entité
void addTag(Entity entity, const char* tag) {
    TagComponent* tagComp = getTagComponent(entity);
    if (tagComp->tagCount < MAX_TAGS) {
        strncpy(tagComp->tags[tagComp->tagCount], tag, MAX_TAG_LENGTH);
        tagComp->tags[tagComp->tagCount][MAX_TAG_LENGTH - 1] = '\0'; // Assurer la terminaison nulle
        tagComp->tagCount++;
        hasTags[entity] = true;
    }
}

void removeTag(Entity entity, const char* tag) {
    if (entity < 0 || entity >= MAX_ENTITIES) return;

    TagComponent* tagComp = &tagComponents[entity];
    int index = findTagIndex(tagComp, tag);
    if (index != -1) {
        for (int i = index; i < tagComp->tagCount - 1; ++i) {
            strncpy(tagComp->tags[i], tagComp->tags[i + 1], MAX_TAG_LENGTH);
        }
        tagComp->tagCount--;
    }
}

void removeAllTags(Entity entity) {
    if (entity < 0 || entity >= MAX_ENTITIES) return;

    TagComponent* tagComp = &tagComponents[entity];
    if (tagComp == NULL) return;

    tagComp->tagCount = 0;

    for (int i = 0; i < MAX_TAGS; ++i) {
        memset(tagComp->tags[i], 0, MAX_TAG_LENGTH); // Réinitialiser la chaîne de caractères
    }
}

// Vérifier si une entité a un tag spécifique
bool hasTag(Entity entity, const char* tag) {
    TagComponent* tagComp = getTagComponent(entity);
    if (tagComp == NULL){
        return false;
    }
    
    for (int i = 0; i < tagComp->tagCount; i++) {
        if (strcmp(tagComp->tags[i], tag) == 0) {
            return true;
        }
    }
    return false;
}

// Fonction pour vérifier si une entité possède un des tags spécifiés
bool hasAnyTag(Event event, ...) {
    // Vérifier que les données de l'événement ne sont pas nulles
    if (event.data == NULL) return false;

    // Convertir event.data en pointeur vers l'entité
    Entity* ptr_entity = (Entity*)event.data;
    if (ptr_entity == NULL) return false;

    // Récupérer l'entité
    Entity entity = *ptr_entity;

    // Initialiser la liste d'arguments
    va_list args;
    va_start(args, event);

    // Parcourir les arguments jusqu'à ce que NULL soit trouvé
    const char* tag;
    while ((tag = va_arg(args, const char*)) != NULL) {
        // Vérifier si l'entité possède le tag courant
        if (hasTag(entity, tag)) {
            va_end(args);
            return true;
        }
    }

    // Terminer la liste d'arguments
    va_end(args);

    // Aucun tag correspondant trouvé
    return false;
}

Entity getFirstEntityWithTag(const char* tag) {
    for (Entity i = 0; i < MAX_ENTITIES; ++i) {
        TagComponent* tagComp = &tagComponents[i];
        if (strcmp(tagComp->tags[i], tag) == 0) {
            return i;
        }
    }
    return INVALID_ENTITY_ID;
}

Entity getLastEntityWithTag(const char* tag) {
    for (Entity i = MAX_ENTITIES - 1; i >= 0; i--) {
        TagComponent* tagComp = &tagComponents[i];
        if (strcmp(tagComp->tags[i], tag) == 0) {
            return i;
        }
    }
    return INVALID_ENTITY_ID;
}

Entity* getEntitiesWithTag(const char* tag, int* outCount) {
    int maxEntities = MAX_ENTITIES;
    Entity* entities = (Entity*)malloc(maxEntities * sizeof(Entity));
    if (entities == NULL) {
        *outCount = 0;
        return NULL;
    }

    int count = 0;

    for (Entity i = 0; i < maxEntities; ++i) {
        if (count >= maxEntities) break;

        TagComponent* tagComp = &tagComponents[i];
        if (findTagIndex(tagComp, tag) != -1) {
            entities[count++] = i;
        }
    }

    *outCount = count;
    return entities;
}