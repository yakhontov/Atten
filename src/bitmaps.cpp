#include <Arduino.h>
#include "bitmaps.h"

const unsigned char *startupBitmaps[] = {
    imFromWillage,
    fresh,
    letsDrink,
    bogdan,
    stillworks};

const int startupIconsCount = sizeof(startupBitmaps) / sizeof(startupBitmaps[0]);

const unsigned char *speakerBitmaps[] = {
    bmp_subwoofer,
    bmp_center,
    bmp_front,
    bmp_rear};
