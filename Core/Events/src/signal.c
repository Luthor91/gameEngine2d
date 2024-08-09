#include "../include/signal.h"
#include <stdlib.h>

// Fonction pour créer un nouveau signal
Signal* Signal_Init(SignalHandler defaultHandler, void* defaultData) {
    Signal* signal = (Signal*)malloc(sizeof(Signal));
    if (signal) {
        signal->slots = NULL;
        if (defaultHandler) {
            Signal_AddSlot(signal, defaultHandler, defaultData);
        }
    }
    return signal;
}

// Fonction pour ajouter un slot à un signal
void Signal_AddSlot(Signal* signal, SignalHandler handler, void* data) {
    if (signal) {
        SignalSlot* slot = (SignalSlot*)malloc(sizeof(SignalSlot));
        if (slot) {
            slot->handler = handler;
            slot->data = data;
            slot->next = signal->slots;
            signal->slots = slot;
        }
    }
}

// Fonction pour émettre un signal
void Signal_Emit(Signal* signal, void* data) {
    if (signal == NULL) return;

    SignalSlot* current = signal->slots;
    while (current != NULL) {
        if (data == NULL) {
            current->handler(current->data);
        } else {
            current->handler(data);
        }
        current = current->next;
    }
}

// Fonction pour détruire un signal et libérer la mémoire
void Signal_Destroy(Signal* signal) {
    if (signal == NULL) return;

    SignalSlot* current = signal->slots;
    while (current != NULL) {
        SignalSlot* next = current->next;
        free(current);
        current = next;
    }
    free(signal);
}
