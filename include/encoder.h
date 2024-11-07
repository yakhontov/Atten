#pragma once
#include "stdint.h"

typedef struct EncoderEvents {
    uint8_t rotate;
    uint8_t press;
    uint8_t longPress;
};

extern EncoderEvents encEvent;

void encoderSetup();
void encoderLoop();