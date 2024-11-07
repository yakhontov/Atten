#pragma once
#include <stdint.h>
#include "speakers.h"

void screenSetup();
void screenLoop();
void screenShowBitmap(const unsigned char *bitmap, uint32_t milliseconds);
void screenShowBalance(SpeakerType spkr, uint32_t milliseconds);
void screenShowMasterVolume();