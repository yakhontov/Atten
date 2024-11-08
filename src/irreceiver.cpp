#include <Arduino.h>
#include <IRremote.hpp>
#include "config.h"
#include "speakers.h"

void irSetup()
{
    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void irLoop()
{
    if (IrReceiver.decode())
    {
        IrReceiver.resume();
        if (IrReceiver.decodedIRData.address == 0x07)
        {
            switch (IrReceiver.decodedIRData.command)
            {
            case 0xE6: // off
                break;
            case 0x7: // vol+
                speakersSetMasterVolume(masterVolume + 1);
                break;
            case 0xB: // vol-
                speakersSetMasterVolume(masterVolume - 1);
                break;
            case 0xF: // mute
                speakersSetMasterMute(!masterMute);
                break;
            case 0x12: // ch+
                speakersSetBalance(Subwoofer, speakers[Subwoofer].balance + 1);
                break;
            case 0x10: // ch-
                speakersSetBalance(Subwoofer, speakers[Subwoofer].balance - 1);
                break;
            case 0x4F: // ch push
                break;
            case 0x60: // up
                speakersSetBalance(Center, speakers[Center].balance + 1);
                break;
            case 0x61: // down
                speakersSetBalance(Center, speakers[Center].balance - 1);
                break;
            case 0x65: // left
                speakersSetBalance(Front, speakers[Front].balance + 1);
                break;
            case 0x62: // right
                speakersSetBalance(Front, speakers[Front].balance - 1);
                break;
            case 0x68: // ok
                break;
            }
        }
    }
}