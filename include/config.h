#pragma once
#include <Arduino.h>
#include <stdint.h>

// Screen
const int SCR_CS = A13, SCR_DC = A14, SCR_RES = A15;

// Encoder
const int ENC_CLK = 12, ENC_DT = 11, ENC_SW = 10, ENC_VCC = 9, ENC_GND = 8;

// IR receiver
const int IR_PIN = 2;

// SpeakerType
const char SUB_PORT = 'A', CENTER_PORT = 'C', FRONT_PORT = 'F', REAR_PORT = 'K';

const int8_t maxVolume = 63;
