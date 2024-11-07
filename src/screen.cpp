#include "screen.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include "config.h"
#include "encoder.h"
#include "icons.h"
#include "speakers.h"

U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, SCR_CS, SCR_DC, SCR_RES);
uint8_t requestRedraw = 1;

void screenRedraw()
{
    requestRedraw = 1;
}

void screenSetup()
{
    u8g2.begin();
    u8g2.setFont(u8g2_font_inb63_mn);
}

void screenLoop()
{
    // u8g2.setFont(u8g2_font_helvR08_tr);
    if (requestRedraw)
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
                u8g2.setCursor(masterVolume < 10 ? 39 : 13, 63);
                u8g2.print(masterVolume);
            }

        } while (u8g2.nextPage());
        requestRedraw = 0;
    }
}