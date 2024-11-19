#include "screen.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include "config.h"
#include "encoder.h"
#include "bitmaps.h"
#include "speakers.h"
#include "log.h"

U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, SCR_CS, SCR_DC, SCR_RES);
// u8g2_font_inb63_mn
// https://github.com/olikraus/u8g2/wiki/fntgrpinconsolata
// 42, 46, 49, 53, 57, 63

struct
{
    unsigned long start;
    unsigned long duration;
} showingBitmap = {0};

int8_t blackScreenMode = 0;

void screenShowBitmap(const unsigned char *bitmap, uint32_t milliseconds)
{
    LOG;
    if (!milliseconds)
        return;
    u8g2.firstPage();
    do
    {
        u8g2.drawXBMP(0, 0, 128, 64, bitmap);
    } while (u8g2.nextPage());
    showingBitmap = {millis(), milliseconds};
}

void screenDrawSpeakers(uint8_t subwoofer, uint8_t center, uint8_t front, uint8_t rear)
{
    u8g2.drawXBMP(0, 0, 128, 64, bpm_speakers);
    u8g2.setDrawColor(0);
    if (!subwoofer)
        u8g2.drawBox(43, 22, 43, 43);
    if (!center)
        u8g2.drawBox(43, 0, 43, 20);
    if (!front)
    {
        u8g2.drawBox(0, 0, 43, 43);
        u8g2.drawBox(86, 0, 43, 43);
    }
    if (!rear)
    {
        u8g2.drawBox(0, 43, 43, 43);
        u8g2.drawBox(86, 43, 43, 43);
    }
    u8g2.setDrawColor(1);
}

void screenShowSpeakers(uint8_t subwoofer, uint8_t center, uint8_t front, uint8_t rear, uint32_t milliseconds)
{
    LOGP(String(subwoofer) + String(center) + String(front) + String(rear));
    if (!milliseconds)
        return;
    u8g2.firstPage();
    do
    {
        screenDrawSpeakers(subwoofer, center, front, rear);
    } while (u8g2.nextPage());
    showingBitmap = {millis(), milliseconds};
}

void screenShowBalance(SpeakerType speakerType, uint32_t milliseconds)
{
    LOG;
    if (!milliseconds)
        return;
    u8g2.firstPage();
    do
    {
        if (speakerType == Subwoofer)
            u8g2.drawXBMP(0, 11, 42, 42, bmp_subsmall);
        else
            screenDrawSpeakers(speakerType == Subwoofer, speakerType == Center, speakerType == Front, speakerType == Rear);
        u8g2.setFontMode(1);
        u8g2.setFont(u8g2_font_inb38_mn);
        int8_t balance = speakers[(int)speakerType].balance;
        if (speakerType == Subwoofer)
            u8g2.setCursor(abs(balance) < 10 ? 54 : 38, 50);
        else
            u8g2.setCursor(abs(balance) < 10 ? 32 : 16, speakerType == Rear ? 38 : 63);
        u8g2.print((balance >= 0 ? "+" : "") + String(balance));
    } while (u8g2.nextPage());
    showingBitmap = {millis(), milliseconds};
}

void screenSetBlackMode(int8_t bsm)
{
    blackScreenMode = bsm;
    if (bsm)
    {
        u8g2.firstPage();
        while (u8g2.nextPage())
            ;
    }
    else
        screenShowMasterVolume();
}

void screenToggleBlackMode()
{
    screenSetBlackMode(!blackScreenMode);
}

void screenShowMasterVolume()
{
    LOG;
    u8g2.firstPage();
    do
    {
        if (masterMute)
        {
            u8g2.drawXBMP(30, 0, 67, 64, bmp_mute);
        }
        else
        {
            u8g2.setFont(u8g2_font_inb63_mn);
            u8g2.setCursor(masterVolume < 10 ? 39 : 13, 62);
            u8g2.print(masterVolume);
        }
    } while (u8g2.nextPage());
    if (blackScreenMode)
        showingBitmap = {millis(), 3000};
}

void screenSetup()
{
    u8g2.begin();
}

void screenEnable(uint8_t enable)
{
    LOGP(String(enable) + " de=" + String(deviceEnabled));
    u8g2.setPowerSave(!enable);
}

void screenLoop()
{
    if (showingBitmap.duration && millis() - showingBitmap.start > showingBitmap.duration)
    {
        LOGP("de=" + String(deviceEnabled) + ", bsm=" + String(blackScreenMode));
        if (deviceEnabled)
        {
            if (blackScreenMode)
                screenSetBlackMode(true);
            else
                screenShowMasterVolume();
        }
        else
        {
            u8g2.firstPage();
            do
            {
                u8g2.clear();
            } while (u8g2.nextPage());
            screenEnable(false);
        }
        showingBitmap.duration = 0;
    }
}