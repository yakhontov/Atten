#pragma once
#include "globals.h"

enum Speakers
{
    Subwoofer,
    Center,
    Front,
    Rear
};

typedef struct
{
    char port;
    bool enabled;
    int balance;
} Speaker;

extern Speaker speakers[];
extern int8_t masterVolume;
extern uint8_t masterMute;