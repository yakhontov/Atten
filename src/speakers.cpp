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
uint8_t deviceEnabled = 1;

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

void speakerSetupRelayPins(SpeakerType speakerType)
{
    switch (speakers[speakerType].port)
    {
    case 'A':
        DDRA |= 0b111111;
        break;
    case 'C':
        DDRC |= 0b111111;
        break;
    case 'F':
        DDRF |= 0b111111;
        break;
    case 'K':
        DDRK |= 0b111111;
        break;
    case 'L':
        DDRL |= 0b111111;
        break;
    }
}

void speakersSetup()
{
    pinMode(POWER_FRONT_SUB, OUTPUT);
    pinMode(POWER_REAR_CENTER, OUTPUT);
    pinMode(POWER_DAC, OUTPUT);
    pinMode(SWITCH_PC, OUTPUT);
    pinMode(LED_STANDBY, OUTPUT);
    for (int i = 0; i < 4; i++)
        speakerSetupRelayPins((SpeakerType)i);
}

void speakersOutVolume(SpeakerType speakerType)
{
    int volume = masterVolume + speakers[speakerType].balance;
    if (masterMute || !speakers[speakerType].enabled)
        volume = 0;
    volume = constrain(volume, 0, 0b111111);
    switch (speakers[speakerType].port)
    {
    case 'A':
        PORTA = (PORTA & 0b11000000) | volume;
        break;
    case 'C':
        PORTC = (PORTC & 0b11000000) | volume;
        break;
    case 'F':
        PORTF = (PORTF & 0b11000000) | volume;
        break;
    case 'K':
        PORTK = (PORTK & 0b11000000) | volume;
        break;
    case 'L':
        PORTL = (PORTL & 0b11000000) | volume;
        break;
    }
}

void speakersLoop()
{
    for (int i = 0; i < 4; i++)
        speakerSetupRelayPins((SpeakerType)i);
}

void speakersLoadVolume()
{
    int8_t v;
    for (int i = 0; i < 4; i++)
    {
        v = (int8_t)EEPROM.read(i);
        if (v >= -maxVolume && v <= maxVolume)
            speakers[i].balance = v;
    }
    v = EEPROM.read(4);
    if (v >= 0 && v <= maxVolume)
        masterVolume = v;
}

void speakersSaveVolume()
{
    screenShowBitmap(bmp_saved, 3000);
    for (int i = 0; i < 4; i++)
        EEPROM.update(i, speakers[i].balance);
    EEPROM.update(4, masterVolume);
}

void speakersSetMode(uint8_t subwoofer, uint8_t center, uint8_t front, uint8_t rear, long delayms = 0)
{
    screenShowSpeakers(subwoofer, center, front, rear, 3000);
    delay(delayms);
    speakers[Subwoofer].enabled = subwoofer;
    speakers[Center].enabled = center;
    speakers[Front].enabled = front;
    speakers[Rear].enabled = rear;
}

void speakersStereo()
{
    masterMute = true;
    speakersSetMode(true, false, true, false, 50);
    digitalWrite(POWER_DAC, HIGH);
    speakersLoadVolume();
    delay(200);
    masterMute = false;
}

void speakersMch()
{
    masterMute = true;
    speakersSetMode(true, true, true, true, 50);
    digitalWrite(POWER_DAC, LOW);
    speakersLoadVolume();
    delay(200);
    masterMute = false;
}

uint8_t speakersIsStereo() { return digitalRead(POWER_DAC); };

int8_t speakersChangeBalance(SpeakerType speakerType, int8_t change) { return speakersSetBalance(speakerType, speakers[speakerType].balance + change); };
int8_t speakersToggleEnabled(SpeakerType speakerType, int8_t enabled) { return speakers[speakerType].enabled = !speakers[speakerType].enabled; };

void powerOn()
{
    deviceEnabled = true;
    speakersStereo();
}

void powerOff()
{
    deviceEnabled = false;
    // clear screen
}
