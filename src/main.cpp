#include "main.h"
#include "config.h"
#include "encoder.h"
#include "screen.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include "bitmaps.h"
#include "irreceiver.h"

void setup(void)
{
    unsigned long seed;
    for (int i = 0; i <= 15; i++)
        seed = (seed << 1) ^ analogRead(i);
    randomSeed(seed);
    Serial.begin(115200);
    speakersSetup();
    encoderSetup();
    screenSetup();
    irSetup();
    seed = random(startupIconsCount);
    screenShowBitmap(startupBitmaps[seed], 3000);
}

void loop(void)
{
    encoderLoop();
    irLoop();
    screenLoop();
    speakersLoop();
}