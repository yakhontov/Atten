#include "screen.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include "config.h"
#include "encoder.h"

U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, SCR_CS, SCR_DC, SCR_RES);
uint8_t needRedraw = 1;

void sreenRedraw()
{
    needRedraw = 1;
}

void screenSetup()
{
    u8g2.begin();
}

void screenLoop()
{
    u8g2.setFont(u8g2_font_helvR08_tr);
    if (needRedraw)
    {
        u8g2.firstPage();
        do
        {
            u8g2.setCursor(0, 20);
            u8g2.print(millis());
        } while (u8g2.nextPage());
        needRedraw = 0;
    }
}