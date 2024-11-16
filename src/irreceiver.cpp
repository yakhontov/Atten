#include <Arduino.h>
#include <IRremote.hpp>
#include "config.h"
#include "speakers.h"
#include "screen.h"
#include "bitmaps.h"
#include "log.h"

void irSetup()
{
    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void togglePc()
{
    LOG;
    screenShowBitmap(bmp_pc, 3000);
    digitalWrite(SWITCH_PC, HIGH);
    delay(600);
    digitalWrite(SWITCH_PC, LOW);
}

void irLoop()
{
    if (IrReceiver.decode())
    {
        LOGP("adr=" + String(IrReceiver.decodedIRData.address) + ", cmd" + String(IrReceiver.decodedIRData.command));
        if (IrReceiver.decodedIRData.address == 0x00)
        {
            if (!deviceEnabled)
            {
                if (IrReceiver.decodedIRData.command == 0x00 || IrReceiver.decodedIRData.command == 0x0C) // off || 0 - stereo/mch
                {
                    powerOn();
                    delay(500);
                    // IrReceiver.resume();
                }
                return;
            }
            switch (IrReceiver.decodedIRData.command)
            {
            case 0x0C: // off
                powerOff();
                delay(500);
                break;
            case 0x38: // tv/av
                togglePc();
                delay(500);
                break;
            case 0x25: // ok
                screenShowBitmap(bmp_load, 3000);
                speakersLoadVolume();
                break;
            case 0x36: // iii
                speakersSaveVolume();
                break;
            case 0x00: // 0 stereo/mch
                if (speakersIsStereo())
                    speakersMch();
                else
                    speakersStereo();
                break;

            case 0x10: // vol+
                speakersSetMasterVolume(masterVolume + 1);
                break;
            case 0x11: // vol-
                speakersSetMasterVolume(masterVolume - 1);
                break;
            case 0x0D: // mute
                speakersSetMasterMute(!masterMute);
                delay(500);
                break;

            case 0x02: // 2 sub+
                speakersChangeBalance(Subwoofer, 1);
                break;
            case 0x01: // 1 sub-
                speakersChangeBalance(Subwoofer, -1);
                break;
            case 0x03: // 3 sub mute
                speakersToggleEnabled(Subwoofer);
                delay(500);
                break;

            case 0x05: // 5 center+
                speakersChangeBalance(Center, 1);
                break;
            case 0x04: // 4 center-
                speakersChangeBalance(Center, -1);
                break;
            case 0x06: // 6 centerr mute
                speakersToggleEnabled(Center);
                delay(500);
                break;

            case 0x08: // 8 rear+
                speakersChangeBalance(Rear, 1);
                break;
            case 0x07: // 7 rear-
                speakersChangeBalance(Rear, -1);
                break;
            case 0x09: // 9 rear mute
                speakersToggleEnabled(Rear);
                delay(500);
                break;

            case 0x16: // psm front+
                speakersChangeBalance(Front, 1);
                break;
            case 0x0E: // ssm front-
                speakersChangeBalance(Front, -1);
                break;
            case 0x26: // sleep front mute
                speakersToggleEnabled(Front);
                delay(500);
                break;
            }
        }
        IrReceiver.resume();
    }
}
