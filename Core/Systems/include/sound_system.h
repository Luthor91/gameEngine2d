#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>

#define MAX_SOUNDS 128  // Nombre maximum de sons que le système peut gérer
#define MAX_SOUND_NAME_LENGTH 64  // Longueur maximale du nom d'un son

// Type de son : soit un effet sonore (chunk), soit une musique
typedef enum SoundType {
    SOUND_TYPE_CHUNK,  // Un effet sonore court (géré avec Mix_Chunk)
    SOUND_TYPE_MUSIC   // Une musique de fond (géré avec Mix_Music)
} SoundType;

// Structure représentant un son
typedef struct Sound {
    union audioData {
        Mix_Chunk *chunk;  // Pointeur vers un effet sonore
        Mix_Music *music;  // Pointeur vers une musique
    } audioData;
    
    SoundType type;  // Type du son (chunk ou music)
    int channel;     // Canal sur lequel le chunk est joué (pour Mix_Chunk uniquement)
    int isPaused;    // Indicateur si le son est en pause (pour Mix_Chunk uniquement)
    char name[MAX_SOUND_NAME_LENGTH];  // Nom d'identification du son
} Sound;

// Initialise le système de son
// Retourne 0 en cas de succès, -1 en cas d'erreur
int Init_SoundSystem();

// Ajoute un son au système
// - path : chemin vers le fichier audio
// - name : nom d'identification du son
// - type : type de son (SOUND_TYPE_CHUNK ou SOUND_TYPE_MUSIC)
// Retourne 0 en cas de succès, -1 en cas d'échec
int AddSound(const char *path, const char *name, SoundType type);

// Joue un son identifié par son nom
// - name : nom du son à jouer
// Retourne 0 en cas de succès, -1 en cas d'échec
int PlaySound(const char *name);

// Met en pause un son identifié par son nom (pour les chunks)
// - name : nom du son à mettre en pause
// Retourne 0 en cas de succès, -1 en cas d'échec
int PauseSound(const char *name);

// Reprend un son identifié par son nom (pour les chunks)
// - name : nom du son à reprendre
// Retourne 0 en cas de succès, -1 en cas d'échec
int ResumeSound(const char *name);

// Libère toutes les ressources allouées par le système de son
void Close_SoundSystem();

#endif // SOUND_SYSTEM_H