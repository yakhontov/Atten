#pragma once
#include <Arduino.h>

const unsigned char mute_mitmap[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xc0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xf0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0xf8, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x7c, 0x00, 0x00, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x0c, 0xfe, 0x00, 0x00,
    0x00, 0x00, 0xc0, 0x7f, 0x00, 0x1e, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x7f, 0x00, 0x8f, 0x3f,
    0x00, 0x00, 0x00, 0x00, 0xfc, 0x7f, 0x00, 0xc7, 0x1f, 0x00, 0x00, 0x00, 0x00, 0xff, 0x7f, 0x00,
    0xe2, 0x0f, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x7f, 0x00, 0xf0, 0x07, 0x00, 0x00, 0x00, 0xf0, 0xff,
    0x7f, 0x00, 0xf8, 0x03, 0x00, 0x00, 0x00, 0xfc, 0xff, 0x7f, 0x00, 0xfc, 0x01, 0x00, 0x00, 0x00,
    0xff, 0xff, 0x7f, 0x00, 0xfe, 0x18, 0x00, 0x00, 0xc0, 0xff, 0xff, 0x7f, 0x00, 0x7f, 0x3c, 0x00,
    0x00, 0xf0, 0xff, 0xff, 0x7f, 0x80, 0x3f, 0x3e, 0x00, 0x00, 0xfc, 0xff, 0xff, 0x7f, 0xc0, 0x1f,
    0x7f, 0x00, 0xfe, 0xff, 0xff, 0xff, 0x7f, 0xe0, 0x0f, 0x7e, 0x00, 0xff, 0xff, 0xff, 0xff, 0x7f,
    0xf0, 0x07, 0xfc, 0x00, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xf8, 0x03, 0xf8, 0x00, 0xff, 0xff, 0xff,
    0xff, 0x7f, 0xfc, 0x31, 0xf8, 0x01, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xfe, 0x78, 0xf0, 0x01, 0xff,
    0xff, 0xff, 0xff, 0x1f, 0x7f, 0x7c, 0xf0, 0x03, 0xff, 0xff, 0xff, 0xff, 0x8f, 0x3f, 0xfe, 0xf0,
    0x03, 0xff, 0xff, 0xff, 0xff, 0xc7, 0x1f, 0xfc, 0xe0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xe3, 0x0f,
    0xf8, 0xe0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf1, 0x07, 0xf8, 0xe1, 0x03, 0xff, 0xff, 0xff, 0xff,
    0xf8, 0x03, 0xf0, 0xe1, 0x07, 0xff, 0xff, 0xff, 0x7f, 0xfc, 0x01, 0xf0, 0xe1, 0x07, 0xff, 0xff,
    0xff, 0x3f, 0xfe, 0x00, 0xf0, 0xc1, 0x07, 0xff, 0xff, 0xff, 0x1f, 0x7f, 0x00, 0xf0, 0xc1, 0x07,
    0xff, 0xff, 0xff, 0x8f, 0x3f, 0x00, 0xf0, 0xc1, 0x07, 0xff, 0xff, 0xff, 0xc7, 0x1f, 0x00, 0xf0,
    0xc1, 0x07, 0xff, 0xff, 0xff, 0xe3, 0x0f, 0x00, 0xf0, 0xe1, 0x07, 0xff, 0xff, 0xff, 0xf1, 0x47,
    0x00, 0xf0, 0xe1, 0x07, 0xff, 0xff, 0xff, 0xf8, 0x63, 0x00, 0xf8, 0xe1, 0x03, 0xff, 0xff, 0x7f,
    0xfc, 0x71, 0x00, 0xf8, 0xe0, 0x03, 0xff, 0xff, 0x3f, 0xfe, 0x78, 0x00, 0xfc, 0xe0, 0x03, 0xff,
    0xff, 0x1f, 0x7f, 0x7c, 0x00, 0xfc, 0xf0, 0x03, 0xff, 0xff, 0x8f, 0x3f, 0x7e, 0x00, 0x7e, 0xf0,
    0x03, 0xff, 0xff, 0xc7, 0x1f, 0x7f, 0x00, 0x7f, 0xf0, 0x01, 0xff, 0xff, 0xe3, 0x8f, 0x7f, 0x80,
    0x3f, 0xf8, 0x01, 0xff, 0xff, 0xf1, 0xc7, 0x7f, 0xc0, 0x1f, 0xf8, 0x00, 0xff, 0xff, 0xf8, 0xe3,
    0x7f, 0xe0, 0x1f, 0xfc, 0x00, 0xfe, 0x7f, 0xfc, 0xf1, 0x7f, 0xf0, 0x0f, 0x7e, 0x00, 0x00, 0x3c,
    0xfe, 0xf8, 0x7f, 0xf0, 0x07, 0x7e, 0x00, 0x00, 0x10, 0x7f, 0xfc, 0x7f, 0xf0, 0x01, 0x3f, 0x00,
    0x00, 0x80, 0x3f, 0xfe, 0x7f, 0xe0, 0x80, 0x3f, 0x00, 0x00, 0xc0, 0x1f, 0xff, 0x7f, 0x60, 0xc0,
    0x1f, 0x00, 0x00, 0xe0, 0x8f, 0xff, 0x7f, 0x00, 0xe0, 0x0f, 0x00, 0x00, 0xf0, 0xc7, 0xff, 0x7f,
    0x00, 0xf0, 0x07, 0x00, 0x00, 0xf8, 0xc3, 0xff, 0x7f, 0x00, 0xfc, 0x03, 0x00, 0x00, 0xfc, 0x01,
    0xff, 0x7f, 0x00, 0xfe, 0x01, 0x00, 0x00, 0xfe, 0x00, 0xfc, 0x7f, 0x00, 0xff, 0x00, 0x00, 0x00,
    0x7f, 0x00, 0xf0, 0x7f, 0x00, 0x7f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0xc0, 0x7f, 0x00, 0x1e, 0x00,
    0x00, 0xc0, 0x1f, 0x00, 0x00, 0x7f, 0x00, 0x0c, 0x00, 0x00, 0xe0, 0x0f, 0x00, 0x00, 0x7c, 0x00,
    0x00, 0x00, 0x00, 0xf0, 0x07, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};