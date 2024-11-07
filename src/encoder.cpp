#include "encoder.h"
#include "config.h"
#include <Arduino.h>
#include <Versatile_RotaryEncoder.h>

Versatile_RotaryEncoder encoder(ENC_CLK, ENC_DT, ENC_SW);
EncoderEvents encEvent = { 0 };

void encoderhandleRotate(int8_t rotation)
{
    if (rotation > 0)
        encEvent.rotate = 2; // CW
    else
        encEvent.rotate = 1; // CCW
}

void encoderhandlePressRelease()
{
    encEvent.press = 1;
}

void encoderhandleLongPressRelease()
{
    encEvent.longPress = 1;
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