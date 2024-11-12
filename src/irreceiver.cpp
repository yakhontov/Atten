#include <Arduino.h>
#include <IRremote.hpp>
#include "config.h"
#include "speakers.h"
#include "screen.h"
#include "bitmaps.h"

void irSetup()
{
    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void togglePc()
{
    screenShowBitmap(bogdan, 3000);
    digitalWrite(SWITCH_PC, HIGH);
    delay(600);
    digitalWrite(SWITCH_PC, LOW);
}

void irLoop()
{
    if (IrReceiver.decode())
    {
        IrReceiver.resume();
        if (IrReceiver.decodedIRData.address == 0x00)
        {
            if (!deviceEnabled)
            {
                if (IrReceiver.decodedIRData.command == 0x00 || IrReceiver.decodedIRData.command == 0x0C) // off || 0 - stereo/mch
                    powerOn();
                return;
            }
            switch (IrReceiver.decodedIRData.command)
            {
            case 0x0C: // off
                powerOff();
                break;
            case 0x38: // tv/av
                togglePc();
                break;
            case 0x25: // ok
                speakersLoad();
                break;
            case 0x36: // iii
                speakersSave();
                break;
            case 0x00: // 0 stereo/mch
                if (speakersIsStereo)
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
                break;

            case 0x02: // 2 sub+
                speakersChangeBalance(Subwoofer, 1);
                break;
            case 0x01: // 1 sub-
                speakersChangeBalance(Subwoofer, 1);
                break;
            case 0x03: // 3 sub mute
                break;

            case 0x05: // 5 center+
                speakersChangeBalance(Subwoofer, 1);
                break;
            case 0x04: // 4 center-
                speakersChangeBalance(Subwoofer, 1);
                break;
            case 0x06: // 6 centerr mute
                speakersSetBalance(Front, speakers[Front].balance + 1);
                break;

            case 0x08: // 8 rear+
                speakersChangeBalance(Subwoofer, 1);
                break;
            case 0x07: // 7 rear-
                speakersChangeBalance(Subwoofer, 1);
                break;
            case 0x09: // 9 rear mute
                speakersSetBalance(Front, speakers[Front].balance + 1);
                break;
            }
        }
    }
}
