#pragma once
#include "globals.h"

enum SpeakerType
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

int8_t speakersSetMasterVolume(int8_t volume);
int8_t speakersSetMasterMute(int8_t volume);
int8_t speakersSetBalance(SpeakerType speakerType, int8_t balance);
