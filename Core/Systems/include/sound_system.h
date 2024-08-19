#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>

#define MAX_SOUNDS 128
#define MAX_SOUND_NAME_LENGTH 64

typedef enum SoundType {
    SOUND_TYPE_CHUNK,
    SOUND_TYPE_MUSIC
} SoundType;

typedef struct Sound {
    union audioData {
        Mix_Chunk *chunk;
        Mix_Music *music;
    } audioData;
    SoundType type;
    int channel;         // Canal de lecture du son (pour Mix_Chunk)
    int isPaused;        // État de la pause (pour Mix_Chunk)
    char name[MAX_SOUND_NAME_LENGTH]; // Nom du son
} Sound;

// Initialise le système de son
int Init_SoundSystem();

// Ajoute un son au système
// path : chemin vers le fichier audio
// name : nom d'identification du son
// type : type de son (SOUND_TYPE_CHUNK ou SOUND_TYPE_MUSIC)
// Retourne 0 en cas de succès, -1 en cas d'échec
int AddSound(const char *path, const char *name, SoundType type);

// Joue un son identifié par son nom
// name : nom du son à jouer
// Retourne 0 en cas de succès, -1 en cas d'échec
int PlaySound(const char *name);

// Met en pause un son identifié par son nom
// name : nom du son à mettre en pause
// Retourne 0 en cas de succès, -1 en cas d'échec
int PauseSound(const char *name);

// Reprend un son identifié par son nom
// name : nom du son à reprendre
// Retourne 0 en cas de succès, -1 en cas d'échec
int ResumeSound(const char *name);

// Libère les ressources du système de son
void Close_SoundSystem();

#endif // SOUND_SYSTEM_H
