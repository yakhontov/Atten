#pragma once
#include <Arduino.h>
#include "Config.h"

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
extern uint8_t deviceEnabled;

void powerOn();
void powerOff();
void speakersSave();
void speakersLoad();
uint8_t speakersIsStereo();
void speakersStereo();
void speakersMch();
int8_t speakersSetMasterVolume(int8_t volume);
int8_t speakersSetMasterMute(int8_t volume);
int8_t speakersSetBalance(SpeakerType speakerType, int8_t balance);
int8_t speakersChangeBalance(SpeakerType speakerType, int8_t change);
int8_t speakersToggleEnabled(SpeakerType speakerType, int8_t enabled);
