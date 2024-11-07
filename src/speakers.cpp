#include <Arduino.h>
#include "speakers.h"
#include "config.h"
#include "screen.h"

Speaker speakers[] = {
    {SUB_PORT, true, 0},
    {CENTER_PORT, true, 0},
    {FRONT_PORT, true, 0},
    {REAR_PORT, true, 0}};

int8_t masterVolume;
uint8_t masterMute;

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

// void setVolume(Atten *atten, int masterVolume, bool masterMute)
// {
// int volume = masterVolume + atten->balance;
// if (masterMute || !atten->enabled)
//     volume = 0;
// volume = constrain(volume, 0, 63);
// switch (atten->port) {
// case 'A':
//     PORTA = volume;
//     break;
// case 'C':
//     PORTC = volume;
//     break;
// case 'F':
//     PORTF = volume;
//     break;
// case 'K':
//     PORTK = volume;
//     break;
// case 'L':
//     PORTL = volume;
//     break;
// }
// }