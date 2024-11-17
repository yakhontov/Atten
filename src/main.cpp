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
    pinMode(POWER_BTN, INPUT_PULLUP);
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
    powerOff();
}

void loop(void)
{
    static int8_t pwrBtnState = 1;
    if (digitalRead(POWER_BTN) != pwrBtnState)
    {
        if (pwrBtnState)
        {
            if (deviceEnabled)
                powerOff();
            else
                powerOn();
        }
        pwrBtnState = !pwrBtnState;
    }
    encoderLoop();
    irLoop();
    screenLoop();
    speakersLoop();
}