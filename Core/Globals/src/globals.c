#include "../include/globals.h"

GameGlobals game = { NULL, NULL , 800, 600 };

bool entityStates[MAX_ENTITIES] = {false};
bool hasSprite[MAX_ENTITIES] = {false};
bool hasPosition[MAX_ENTITIES] = {false};
bool hasVelocity[MAX_ENTITIES] = {false};
bool hasInput[MAX_ENTITIES] = {false};
bool hasTransform[MAX_ENTITIES] = {false};
bool hasAnimation[MAX_ENTITIES] = {false};
bool hasHitbox[MAX_ENTITIES] = {false};
bool hasSize[MAX_ENTITIES] = {false};
bool hasTags[MAX_ENTITIES] = {false};
bool hasDatas[MAX_ENTITIES] = {false};