#pragma once
#include "globals.h"

typedef struct
{
    char port;
    bool enabled;
    int balance;
} Atten;

extern Atten sub, center, front, rear;

extern int8_t masterVolume;
extern uint8_t masterMute;