#include "main.h"
#include "config.h"
#include "encoder.h"
#include "screen.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include "bitmaps.h"
#include "irreceiver.h"
#include "log.h"

void setup(void)
{
    Serial.begin(115200);
    LOG;
    unsigned long seed;
    for (int i = 0; i <= 15; i++)
        seed = (seed << 1) ^ analogRead(i);
    randomSeed(seed);
    speakersSetup();
    encoderSetup();
    screenSetup();
    irSetup();
    powerOn();
}

void loop(void)
{
    encoderLoop();
    irLoop();
    screenLoop();
    speakersLoop();
}