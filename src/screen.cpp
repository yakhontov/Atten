#include "screen.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include "config.h"
#include "encoder.h"
#include "bitmaps.h"
#include "speakers.h"

U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, SCR_CS, SCR_DC, SCR_RES);
uint8_t requestRedraw = 1;

void screenRedraw()
{
    requestRedraw = 1;
}

struct
{
    unsigned long start;
    unsigned long duration;
    unsigned char *bitmap;
    char text[4];
} showingBitmap = {0};

void screenShowBitmap(unsigned char *bitmap, uint32_t milliseconds)
{
    showingBitmap = {millis(), milliseconds, bitmap, 0};
    screenRedraw();
}

void screenShowParameter(unsigned char *bitmap, int8_t value, uint32_t milliseconds)
{
}

void screenSetup()
{
    u8g2.begin();
    u8g2.setFont(u8g2_font_inb63_mn);
}

void screenLoop()
{
    if (showingBitmap.bitmap && millis() - showingBitmap.start > showingBitmap.duration)
    {
        showingBitmap.bitmap = NULL;
        requestRedraw = 1;
    }

    if (requestRedraw)
    {
        u8g2.firstPage();
        do
        {
            if (showingBitmap.bitmap)
            {
                u8g2.drawXBMP(0, 0, 128, 64, showingBitmap.bitmap);
                u8g2.setCursor(masterVolume < 10 ? 39 : 13, 63);
                u8g2.print(masterVolume);
            }
            else
            {
                if (masterMute)
                {
                    u8g2.drawXBMP(30, 0, 67, 64, mute_mitmap);
                }
                else
                {
                    u8g2.setCursor(masterVolume < 10 ? 39 : 13, 63);
                    u8g2.print(masterVolume);
                }
            }
        } while (u8g2.nextPage());
        requestRedraw = 0;
    }
}