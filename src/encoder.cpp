#include "encoder.h"
#include "config.h"
#include <Arduino.h>
#include <Versatile_RotaryEncoder.h>
#include "menu.h"
#include "menu.h"
#include "screen.h"

Versatile_RotaryEncoder encoder(ENC_CLK, ENC_DT, ENC_SW);
EncoderEvents encEvent = {0};

void encoderhandleRotate(int8_t rotation)
{
    if (rotation > 0) // CW
        mui.prevField();
    else // CCW
        mui.nextField();
    sreenRedraw();
}

void encoderhandlePressRelease()
{
    mui.sendSelect();
    sreenRedraw();
}

void encoderhandleLongPressRelease()
{
    mui.sendSelectWithExecuteOnSelectFieldSearch();
    sreenRedraw();
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
