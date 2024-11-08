#include "main.h"
#include "config.h"
#include "encoder.h"
#include "screen.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include "bitmaps.h"
#include "irreceiver.h"

// https://github.com/olikraus/u8g2/blob/master/sys/arduino/u8g2_page_buffer/MUIInputVersatileRotaryEncoder/MUIInputVersatileRotaryEncoder.ino

// Pics creation:
// https://onlinepngtools.com/create-monochrome-png
// https://javl.github.io/image2cpp/

void setup(void)
{
    Serial.begin(115200);
    encoderSetup();
    screenSetup();
    irSetup();
    unsigned long seed;
    for (int i = 0; i <= 15; i++)
        seed = (seed << 1) ^ analogRead(i);
    randomSeed(seed);
    seed = random(startupIconsCount);
    Serial.print(' ');
    Serial.println(seed);
    screenShowBitmap(startupBitmaps[seed], 3000);
}

void loop(void)
{
    encoderLoop();
    irLoop();
    screenLoop();
}