#include <Arduino.h>
#include <EEPROM.h>
#include "speakers.h"
#include "config.h"
#include "screen.h"
#include "bitmaps.h"
#include "log.h"

Speaker speakers[] = {
    {SUB_PORT, 1, 0},
    {CENTER_PORT, 1, 0},
    {FRONT_PORT, 1, 0},
    {REAR_PORT, 1, 0}};

int8_t masterVolume = 0;
int8_t masterMute = 0;
int8_t deviceEnabled = 1; // При старте устройство должно быть включено, чтобы показать картинку. Дальше оно выключится само

int8_t speakersSetMasterVolume(int8_t volume)
{
    LOGP(volume);
    masterMute = 0;
    masterVolume = constrain(volume, 0, maxVolume);
    screenShowMasterVolume();
    return masterVolume;
}

int8_t speakersSetMasterMute(int8_t mute)
{
    LOGP(mute);
    masterMute = mute;
    screenShowMasterVolume();
    return masterMute;
}

int8_t speakersChangeBalance(SpeakerType speakerType, int8_t change)
{
    LOGP(String(speakerType) + " " + String(change));

    int8_t balance = constrain(speakers[speakerType].balance + change, -maxVolume, maxVolume);
    speakers[speakerType].enabled = 1;
    speakers[speakerType].balance = balance;
    screenShowBalance(speakerType, 3000);
    return balance;
};

int8_t speakersToggleEnabled(SpeakerType speakerType)
{
    LOGP(String(speakerType));
    speakers[speakerType].enabled = !speakers[speakerType].enabled;
    screenShowSpeakers(speakers[Subwoofer].enabled, speakers[Center].enabled, speakers[Front].enabled, speakers[Rear].enabled, 3000);
    return speakers[speakerType].enabled;
};

void speakerSetupRelayPins(SpeakerType speakerType)
{
    switch (speakers[speakerType].port)
    {
    case 'A':
        DDRA |= 0b111111;
        break;
    case 'C':
        DDRC |= 0b111111;
        break;
    case 'F':
        DDRF |= 0b111111;
        break;
    case 'K':
        DDRK |= 0b111111;
        break;
    case 'L':
        DDRL |= 0b111111;
        break;
    }
}

void speakersSetup()
{
    pinMode(POWER_FRONT_SUB, OUTPUT);
    pinMode(POWER_REAR_CENTER, OUTPUT);
    pinMode(POWER_DAC, OUTPUT);
    pinMode(SWITCH_PC, OUTPUT);
    pinMode(LED_STANDBY, OUTPUT);
    pinMode(STEREO_BTN, INPUT_PULLUP);
    pinMode(MCH_BTN, INPUT_PULLUP);
    for (int i = 0; i < 4; i++)
        speakerSetupRelayPins((SpeakerType)i);
}

void speakersOutVolume(SpeakerType speakerType)
{
    int volume = masterVolume + speakers[speakerType].balance;
    if (masterMute || !speakers[speakerType].enabled)
        volume = 0;
    volume = 0b111111 - constrain(volume, 0, 0b111111); // Инверсия громкости. Обусловлено схемотехникой
    switch (speakers[speakerType].port)
    {
    case 'A':
        PORTA = (PORTA & 0b11000000) | volume;
        break;
    case 'C':
        PORTC = (PORTC & 0b11000000) | volume;
        break;
    case 'F':
        PORTF = (PORTF & 0b11000000) | volume;
        break;
    case 'K':
        PORTK = (PORTK & 0b11000000) | volume;
        break;
    case 'L':
        PORTL = (PORTL & 0b11000000) | volume;
        break;
    }
}

void speakersLoop()
{
    static int8_t stereoBtnState = 1;
    if (digitalRead(STEREO_BTN) != stereoBtnState)
    {
        stereoBtnState = !stereoBtnState;
        if (stereoBtnState)
            speakersSwitchToStereo();
    }

    static int8_t mchBtnState = 1;
    if (digitalRead(MCH_BTN) != mchBtnState)
    {
        mchBtnState = !mchBtnState;
        if (mchBtnState)
            speakersSwitchToMch();
    }

    for (int i = 0; i < 4; i++)
        speakersOutVolume((SpeakerType)i);
}

void speakersLoadVolume()
{
    LOG;
    int8_t v;
    for (int i = 0; i < 4; i++)
    {
        v = (int8_t)EEPROM.read(i);
        if (v >= -maxVolume && v <= maxVolume)
            speakers[i].balance = v;
    }
    v = EEPROM.read(4);
    if (v >= 0 && v <= maxVolume)
        masterVolume = v;
}

void speakersSaveVolume()
{
    LOG;
    screenShowBitmap(bmp_saved, 3000);
    for (int i = 0; i < 4; i++)
        EEPROM.update(i, speakers[i].balance);
    EEPROM.update(4, masterVolume);
}

void speakersSetMode(int8_t subwoofer, int8_t center, int8_t front, int8_t rear)
{
    LOGP(String(subwoofer) + String(center) + String(front) + String(rear));
    for (int i = 0; i < 4; i++) // При смене режима работы сначала глушим все динамики. Включатся они сами в основном цикле программы
        speakersOutVolume((SpeakerType)i);
    delay(50); // Ждем пока пройдут переходные процессы
    // digitalWrite(POWER_FRONT_SUB, subwoofer || front); // При необходимости включаем питание саба и фронта
    // digitalWrite(POWER_REAR_CENTER, center || rear);   // При необходимости включаем питание центра и тыла
    //  Активируем соответстующие каналы
    speakers[Subwoofer].enabled = subwoofer;
    speakers[Center].enabled = center;
    speakers[Front].enabled = front;
    speakers[Rear].enabled = rear;
}

void speakersSwitchToStereo(int8_t showPicture)
{
    LOG;
    if (showPicture) // Картинку можно отключить, чтобы не мешала при старте системы
        screenShowSpeakers(true, false, true, false, 3000);
    speakersSetMode(true, false, true, false);
    digitalWrite(POWER_DAC, HIGH); // В стерео режиме включаем DAC
    digitalWrite(POWER_REAR_CENTER, LOW);
    speakersLoadVolume(); // При переключении режима перезагружаем значение громкости из EEPROM
    delay(200);           // Ждем пока пройдут переходные процессы
}

void speakersSwitchToMch(int8_t showPicture)
{
    LOG;
    if (showPicture) // Картинку можно отключить, чтобы не мешала при старте системы
        screenShowSpeakers(true, true, true, true, 3000);
    speakersSetMode(true, true, true, true);
    digitalWrite(POWER_DAC, LOW); // В режиме MCH отключаем DAC
    digitalWrite(POWER_REAR_CENTER, HIGH);
    speakersLoadVolume(); // При переключении режима перезагружаем значение громкости из EEPROM
    delay(200);           // Ждем пока пройдут переходные процессы
}

int8_t speakersIsStereo()
{
    return digitalRead(POWER_DAC); // Включен ли стерео режим определяем по факту включенного DAC
}

void powerOn(bool stereoMode)
{
    LOG;
    deviceEnabled = true;
    blackScreenMode = false;
    digitalWrite(LED_STANDBY, LOW);
    digitalWrite(POWER_FRONT_SUB, HIGH);
    screenEnable(true);
    screenShowBitmap(startupBitmaps[random(startupIconsCount)], 3000);
    if (stereoMode)
        speakersSwitchToStereo(false); // При включении скрываем картику переключения режима, чтобы она не перекрывала заставку
    else
        speakersSwitchToMch(false);
}

void powerOff()
{
    LOG;
    deviceEnabled = false;
    digitalWrite(POWER_DAC, LOW);
    digitalWrite(POWER_FRONT_SUB, LOW);
    digitalWrite(POWER_REAR_CENTER, LOW);
    digitalWrite(LED_STANDBY, HIGH);
    if (millis() > 500)
        screenShowBitmap(startupBitmaps[random(startupIconsCount)], 3000);
}
