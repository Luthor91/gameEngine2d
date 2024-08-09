#ifndef SIGNAL_H
#define SIGNAL_H

#include <stddef.h>  // Pour le type size_t

#define DEFAULT_SIGNAL Signal_Init(NULL, NULL)

// Type de fonction pour les gestionnaires de signaux
typedef void (*SignalHandler)(void *data);

// Structure représentant un slot
typedef struct SignalSlot {
    SignalHandler handler;  // Fonction de gestion
    void* data;
    struct SignalSlot* next; // Prochain slot dans la liste
} SignalSlot;

// Structure représentant un signal
typedef struct Signal {
    SignalSlot* slots;  // Liste des slots
} Signal;

// Fonction pour créer un nouveau signal
Signal* Signal_Init(SignalHandler defaultHandler, void* defaultData);

// Fonction pour ajouter un slot à un signal
void Signal_AddSlot(Signal* signal, SignalHandler handler, void* data);

// Fonction pour émettre un signal
void Signal_Emit(Signal* signal, void* data);

// Fonction pour détruire un signal et libérer la mémoire
void Signal_Destroy(Signal* signal);

#endif // SIGNAL_H