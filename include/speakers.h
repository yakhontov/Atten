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
    int8_t enabled;
    int8_t balance;
} Speaker;

extern Speaker speakers[];
extern int8_t masterVolume;
extern uint8_t masterMute;
extern uint8_t deviceEnabled;

void powerOn();
void powerOff();
void speakersSaveVolume();
void speakersLoadVolume();
uint8_t speakersIsStereo();
void speakersStereo(uint32_t show = 3000);
void speakersMch();
void speakersSetup();
void speakersLoop();
int8_t speakersSetMasterVolume(int8_t volume);
int8_t speakersSetMasterMute(int8_t volume);
int8_t speakersSetBalance(SpeakerType speakerType, int8_t balance);
int8_t speakersChangeBalance(SpeakerType speakerType, int8_t change);
int8_t speakersToggleEnabled(SpeakerType speakerType);
void speakersSetMode(int8_t subwoofer, int8_t center, int8_t front, int8_t rear, long delayms = 0, uint32_t show = 3000);
