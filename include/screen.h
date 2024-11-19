#pragma once
#include <stdint.h>
#include "speakers.h"

extern int8_t blackScreenMode;

void screenSetup();
void screenLoop();
void screenShowBitmap(const unsigned char *bitmap, uint32_t milliseconds);
void screenShowSpeakers(uint8_t subwoofer, uint8_t center, uint8_t front, uint8_t rear, uint32_t milliseconds);
void screenShowBalance(SpeakerType spkr, uint32_t milliseconds);
void screenShowMasterVolume();
void screenEnable(uint8_t enable);
void screenToggleBlackMode();
