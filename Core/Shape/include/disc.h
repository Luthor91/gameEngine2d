#ifndef DISC_H
#define DISC_H

// Structure de données pour un disque
typedef struct Disc {
    Point2D* center; // Centre du disque
    int radius; // Rayon du disque
    Color* color; // Couleur du disque
} Disc;

// Fonction pour initialiser un disque
Disc* Disc_Init(Point2D* center, int radius, Color* color);


#endif // DISC_H