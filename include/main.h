#include <Arduino.h>
#include <stdint.h>

// Screen
const int SCR_CS=A13, SCR_DC=A14, SCR_RES=A15;

// Encoder
const int ENC_CLK=12, ENC_DT=11, ENC_SW=10, ENC_VCC=9, ENC_GND=8;

void EnableEnc() {
	pinMode(ENC_GND, OUTPUT);
	digitalWrite(ENC_GND, 0);
	pinMode(ENC_VCC, OUTPUT);
	digitalWrite(ENC_VCC, 1);
}

typedef struct Atten {
	char port;
	bool enabled;
	int balance;
};

void outVolume(Atten* atten, int masterVolume, bool masterMute) {
	int volume = masterVolume + atten->balance;
	if(masterMute || !atten->enabled)
		volume = 0;
	volume = constrain(volume, 0, 63);
	switch(atten -> port) {
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