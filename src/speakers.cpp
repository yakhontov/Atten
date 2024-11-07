#include <Arduino.h>
#include "speakers.h"
#include "config.h"

Atten sub = {SUB_PORT, true, 0};
Atten center = {CENTER_PORT, true, 0};
Atten front = {FRONT_PORT, true, 0};
Atten rear = {REAR_PORT, true, 0};

int8_t masterVolume;
uint8_t masterMute;

void setVolume(Atten *atten, int masterVolume, bool masterMute)
{
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
}