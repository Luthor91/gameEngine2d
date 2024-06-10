#ifndef ANIMATION_H
#define ANIMATION_H


typedef struct RenderingObject {
    void* object; // Pointeur vers l'objet spécifique (Triangle, Rectangle, Circle, etc.)
    void* renderFunction; // Pointeur vers la fonction de rendu
} RenderingObject;


#endif // ANIMATION_FRAME_H