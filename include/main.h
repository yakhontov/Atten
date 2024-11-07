#pragma once
#include "config.h"
#include <Arduino.h>
#include <stdint.h>

void outVolume(Atten* atten, int masterVolume, bool masterMute)
{
    int volume = masterVolume + atten->balance;
    if (masterMute || !atten->enabled)
        volume = 0;
    volume = constrain(volume, 0, 63);
    switch (atten->port) {
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