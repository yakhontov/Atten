#include <Arduino.h>
#include <EEPROM.h>
#include "speakers.h"
#include "config.h"
#include "screen.h"
#include "bitmaps.h"

Speaker speakers[] = {
    {SUB_PORT, true, 0},
    {CENTER_PORT, true, 0},
    {FRONT_PORT, true, 0},
    {REAR_PORT, true, 0}};

int8_t masterVolume = 0;
uint8_t masterMute = 1;
uint8_t deviceEnabled = 0;

int8_t speakersSetBalance(SpeakerType speakerType, int8_t balance)
{
    speakers[speakerType].balance = constrain(balance, -maxVolume, maxVolume);
    screenShowBalance(speakerType, 3000);
    return speakers[speakerType].balance;
}

int8_t speakersSetMasterVolume(int8_t volume)
{
    masterMute = 0;
    masterVolume = constrain(volume, 0, maxVolume);
    screenShowMasterVolume();
    return masterVolume;
}

int8_t speakersSetMasterMute(int8_t mute)
{
    masterMute = mute;
    screenShowMasterVolume();
    return masterMute;
}

void speakerOutVolume(SpeakerType speakerType)
{
    int volume = masterVolume + speakers[speakerType].balance;
    if (masterMute || !speakers[speakerType].enabled)
        volume = 0;
    volume = constrain(volume, 0, maxVolume);
    switch (speakers[speakerType].port)
    {
    case 'A':
        PORTA = volume;
        break;
    case 'C':
        PORTC = volume;
        break;
    case 'F':
        PORTF = volume;
        break;
    case 'K':
        PORTK = volume;
        break;
    case 'L':
        PORTL = volume;
        break;
    }
}

void speakersLoad()
{
    screenShowBitmap(letsDrink, 3000);
    int8_t v;
    v = EEPROM.read(0);
    if (v >= 0 && v <= maxVolume)
        masterVolume = v;
    for (int i = 1; i < 5; i++)
    {
        v = (int8_t)EEPROM.read(i);
        if (v >= -maxVolume && v <= maxVolume)
            speakers[i].balance = v;
    }
}

void speakersSave()
{
    screenShowBitmap(stillworks, 3000);
    EEPROM.update(0, masterVolume);
    for (int i = 1; i < 5; i++)
        EEPROM.update(i, (uint8_t)speakers[i].balance);
}

void speakersStereo()
{
    screenShowBitmap(stillworks, 3000);
    masterMute = true;
    digitalWrite(POWER_DAC, HIGH);
    speakersLoad();
    speakers[Subwoofer].enabled = true;
    speakers[Center].enabled = false;
    speakers[Front].enabled = true;
    speakers[Rear].enabled = false;
    delay(250);
    masterMute = false;
}

void speakersMch()
{
    screenShowBitmap(imFromWillage, 3000);
    masterMute = true;
    digitalWrite(POWER_DAC, LOW);
    speakersLoad();
    speakers[Subwoofer].enabled = true;
    speakers[Center].enabled = true;
    speakers[Front].enabled = true;
    speakers[Rear].enabled = true;
    delay(250);
    masterMute = false;
}

void powerOn()
{
    // MUTE + delay(250) + POWER_FRONT_SUB=0, POWER_REAR_CENTER=0
    deviceEnabled = true;
    speakersStereo();
}

void powerOff()
{
    deviceEnabled = false;
    // clear screen
}
