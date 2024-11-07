#include "screen.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include "config.h"
#include "encoder.h"
#include "bitmaps.h"
#include "speakers.h"

U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, SCR_CS, SCR_DC, SCR_RES);
// u8g2_font_inb63_mn
// https://github.com/olikraus/u8g2/wiki/fntgrpinconsolata
// 42, 46, 49, 53, 57, 63

struct
{
    unsigned long start;
    unsigned long duration;
} showingBitmap = {0};

void screenShowBitmap(const unsigned char *bitmap, uint32_t milliseconds)
{
    if (!milliseconds)
        return;
    u8g2.firstPage();
    do
    {
        u8g2.drawXBMP(0, 0, 128, 64, bitmap);
    } while (u8g2.nextPage());
    showingBitmap = {millis(), milliseconds};
}

void screenShowBalance(SpeakerType speakerType, uint32_t milliseconds)
{
    if (!milliseconds)
        return;
    u8g2.firstPage();
    do
    {
        u8g2.setBitmapMode(1);
        u8g2.setFontMode(1);

        // u8g2.drawXBMP(0, 0, 128, 64, speakerBitmaps[(int)speakerType]);
        // u8g2.drawFrame(0, 0, 128, 64);
        u8g2.setFont(u8g2_font_inb46_mn);
        int8_t balance = speakers[(int)speakerType].balance;
        u8g2.setCursor(abs(balance) < 10 ? 27 : 6, speakerType == Subwoofer ? 54 : (speakerType == Rear ? 45 : 63)); // u8g2_font_inb46_mn (abs(balance) < 10 ? 27 : 6, speakerType == Subwoofer ? 54 : (speakerType == Rear ? 45 : 63))
        u8g2.print((balance >= 0 ? "+" : "") + String(balance));

        // u8g2.setFont(u8g2_font_inb46_mn);
        // int8_t balance = speakers[(int)speakerType].balance;
        // u8g2.setCursor(abs(balance) < 10 ? 39 : 13, speakerType == Subwoofer ? 60 : (speakerType == Rear ? 0 : 20));
        // u8g2.print((balance >= 0 ? "+" : "") + String(balance));

    } while (u8g2.nextPage());
    showingBitmap = {millis(), milliseconds};
}

void screenShowMasterVolume()
{
    u8g2.firstPage();
    do
    {
        if (masterMute)
        {
            u8g2.drawXBMP(30, 0, 67, 64, mute_mitmap);
        }
        else
        {
            u8g2.setFont(u8g2_font_inb63_mn);
            u8g2.setCursor(masterVolume < 10 ? 39 : 13, 63);
            u8g2.print(masterVolume);
        }
    } while (u8g2.nextPage());
}

void screenSetup()
{
    u8g2.begin();
}

void screenLoop()
{
    if (showingBitmap.duration && millis() - showingBitmap.start > showingBitmap.duration)
    {
        showingBitmap.duration = 0;
        screenShowMasterVolume();
    }
}