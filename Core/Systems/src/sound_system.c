#include "../include/sound_system.h"

// Allocation dynamique des sons
static Sound* sounds = NULL;
static int soundCount = 0;

// Initialisation du système audio
int Init_SoundSystem() {
    if (sounds != NULL) {
        free(sounds);  // Libérer toute mémoire allouée avant de réinitialiser
    }
    
    sounds = (Sound*)malloc(sizeof(Sound) * MAX_SOUNDS);  // Allocation dynamique de l'espace pour les sons
    if (!sounds) {
        printf("Error: Unable to allocate memory for sounds.\n");
        return -1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Failed to initialize SDL_mixer: %s\n", Mix_GetError());
        free(sounds);
        sounds = NULL;
        return -1;
    }

    return 0;
}

// Ajouter un son au système
int AddSound(const char *path, const char *name, SoundType type) {
    if (soundCount >= MAX_SOUNDS) {
        printf("Error: Sound system is full.\n");
        return -1;
    }

    Sound *sound = &sounds[soundCount++];  // Récupération du prochain slot
    strncpy(sound->name, name, MAX_SOUND_NAME_LENGTH - 1);
    sound->name[MAX_SOUND_NAME_LENGTH - 1] = '\0';  // Assurer la terminaison nulle du nom

    if (type == SOUND_TYPE_CHUNK) {
        sound->audioData.chunk = Mix_LoadWAV(path);
        if (!sound->audioData.chunk) {
            printf("Failed to load WAV file: %s\n", Mix_GetError());
            return -1;
        }
        sound->type = SOUND_TYPE_CHUNK;
        sound->channel = -1;
        sound->isPaused = 0;
    } else if (type == SOUND_TYPE_MUSIC) {
        sound->audioData.music = Mix_LoadMUS(path);
        if (!sound->audioData.music) {
            printf("Failed to load music file: %s\n", Mix_GetError());
            return -1;
        }
        sound->type = SOUND_TYPE_MUSIC;
        sound->channel = -1;
        sound->isPaused = 0;
    } else {
        printf("Error: Unknown sound type.\n");
        return -1;
    }

    return 0;
}

// Recherche d'un son par son nom
static Sound* findSoundByName(const char *name) {
    for (int i = 0; i < soundCount; ++i) {
        if (strcmp(name, sounds[i].name) == 0) {
            return &sounds[i];
        }
    }
    return NULL;
}

// Jouer un son
int PlaySound(const char *name) {
    Sound *sound = findSoundByName(name);
    if (!sound) {
        printf("Error: Sound not found.\n");
        return -1;
    }

    if (sound->type == SOUND_TYPE_CHUNK) {
        if (sound->isPaused) {
            Mix_Resume(sound->channel);
            sound->isPaused = 0;
        } else {
            sound->channel = Mix_PlayChannel(-1, sound->audioData.chunk, 0);
            if (sound->channel == -1) {
                printf("Failed to play sound: %s\n", Mix_GetError());
                return -1;
            }
        }
    } else if (sound->type == SOUND_TYPE_MUSIC) {
        if (Mix_PlayingMusic()) {
            printf("Error: Music is already playing.\n");
            return -1;
        }
        if (Mix_PlayMusic(sound->audioData.music, -1) == -1) {
            printf("Failed to play music: %s\n", Mix_GetError());
            return -1;
        }
    }

    return 0;
}

// Mettre en pause un son
int PauseSound(const char *name) {
    Sound *sound = findSoundByName(name);
    if (!sound) {
        printf("Error: Sound not found.\n");
        return -1;
    }

    if (sound->type == SOUND_TYPE_CHUNK && sound->channel != -1) {
        Mix_Pause(sound->channel);
        sound->isPaused = 1;
    } else if (sound->type == SOUND_TYPE_MUSIC) {
        Mix_PauseMusic();
        sound->isPaused = 1;
    } else {
        printf("Error: Sound is not playing or not a chunk.\n");
        return -1;
    }

    return 0;
}

// Reprendre un son
int ResumeSound(const char *name) {
    Sound *sound = findSoundByName(name);
    if (!sound) {
        printf("Error: Sound not found.\n");
        return -1;
    }

    if (sound->type == SOUND_TYPE_CHUNK && sound->isPaused) {
        Mix_Resume(sound->channel);
        sound->isPaused = 0;
    } else if (sound->type == SOUND_TYPE_MUSIC && sound->isPaused) {
        Mix_ResumeMusic();
        sound->isPaused = 0;
    } else {
        printf("Error: Sound is not paused or not a chunk.\n");
        return -1;
    }

    return 0;
}

// Libérer les ressources et fermer le système de son
void Close_SoundSystem() {
    for (int i = 0; i < soundCount; ++i) {
        if (sounds[i].type == SOUND_TYPE_CHUNK && sounds[i].audioData.chunk) {
            Mix_FreeChunk(sounds[i].audioData.chunk);
        } else if (sounds[i].type == SOUND_TYPE_MUSIC && sounds[i].audioData.music) {
            Mix_FreeMusic(sounds[i].audioData.music);
        }
    }

    free(sounds);  // Libérer la mémoire allouée pour les sons
    sounds = NULL;
    soundCount = 0;

    Mix_CloseAudio();
}