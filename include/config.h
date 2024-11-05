#pragma once
#include <Arduino.h>
#include <stdint.h>

// Screen
const int SCR_CS=A13, SCR_DC=A14, SCR_RES=A15;

// Encoder
const int ENC_CLK=12, ENC_DT=11, ENC_SW=10, ENC_VCC=9, ENC_GND=8;

typedef struct Atten {
	char port;
	bool enabled;
	int balance;
};

Atten sub = {'A', true, 0};
Atten center = {'C', true, 0};
Atten front = {'F', true, 0};
Atten rear = {'K', true, 0};
