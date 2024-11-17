#pragma once
#include <Arduino.h>
#include <stdint.h>

// Screen
const int SCR_CS = A13, SCR_DC = A14, SCR_RES = A15;

// Encoder input
const int ENC_CLK = 12, ENC_DT = 11, ENC_SW = 10, ENC_VCC = 9, ENC_GND = 8;

const int IR_PIN = 2; // IR receiver input

const int POWER_FRONT_SUB = 7;   // питание левого, правого каналов и сабвуфера (PB0)
const int POWER_REAR_CENTER = 6; // питание тылов и центра(PB1)
const int POWER_DAC = 5;         // питание stereo DAC (PB3)
const int SWITCH_PC = 4;         // замыкание кнопки питания компа (PB2)
const int LED_STANDBY = 3;       // выход на светодиод дежурного режима
const int POWER_BTN = A6;

// SpeakerType
const char SUB_PORT = 'A', CENTER_PORT = 'C', FRONT_PORT = 'F', REAR_PORT = 'K';

const int8_t maxVolume = 63;
