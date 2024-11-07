#pragma once
#include <stdint.h>

void screenSetup();
void screenLoop();
void screenRedraw();
void screenShowBitmap(unsigned char *bitmap, uint32_t milliseconds);
void screenShowParameter(unsigned char *bitmap, int8_t value, uint32_t milliseconds);
