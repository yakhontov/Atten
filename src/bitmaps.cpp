#include <Arduino.h>
#include "bitmaps.h"

const unsigned char *startupIcons[] = {
    imFromWillage,
    fresh,
    letsDrink};

const int startupIconsCount = sizeof(startupIcons) / sizeof(startupIcons[0]);