#include "encoder.h"
#include "config.h"
#include <Arduino.h>
#include <Versatile_RotaryEncoder.h>
#include "screen.h"
#include "speakers.h"
#include "log.h"

Versatile_RotaryEncoder encoder(ENC_CLK, ENC_DT, ENC_SW);

void encoderhandleRotate(int8_t rotation)
{
    LOGP(rotation);
    masterMute = 0;
    if (rotation < 0) // CW
        speakersSetMasterVolume(masterVolume + 1);
    else // CCW
        speakersSetMasterVolume(masterVolume - 1);
}

void encoderhandlePressRelease()
{
    LOG;
    if (speakersIsStereo())
        speakersMch();
    else
        speakersStereo();
}

void encoderhandleLongPressRelease()
{
    speakersSaveVolume();
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
    //if (deviceEnabled)
        encoder.ReadEncoder();
}
