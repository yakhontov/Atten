#include "encoder.h"
#include "config.h"
#include <Arduino.h>
#include <Versatile_RotaryEncoder.h>
#include "screen.h"
#include "speakers.h"

Versatile_RotaryEncoder encoder(ENC_CLK, ENC_DT, ENC_SW);

void encoderhandleRotate(int8_t rotation)
{
    masterMute = 0;
    if (rotation < 0) // CW
        masterVolume++;
    else // CCW
        masterVolume--;
    masterVolume = constrain(masterVolume, 0, maxVolume);
    screenRedraw();
}

void encoderhandlePressRelease()
{
    masterMute = !masterMute;
    screenRedraw();
}

void encoderhandleLongPressRelease()
{
    // mui.sendSelectWithExecuteOnSelectFieldSearch();
    // sreenRedraw();
}

void encoderEnablePwr()
{
    pinMode(ENC_GND, OUTPUT);
    digitalWrite(ENC_GND, 0);
    pinMode(ENC_VCC, OUTPUT);
    digitalWrite(ENC_VCC, 1);
}

void encoderSetup()
{
    encoderEnablePwr();
    encoder.setHandleRotate(encoderhandleRotate);
    encoder.setHandlePressRelease(encoderhandlePressRelease);
    encoder.setHandleLongPressRelease(encoderhandleLongPressRelease);
}

void encoderLoop()
{
    encoder.ReadEncoder();
}
