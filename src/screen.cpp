#include "screen.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include <MUIU8g2.h>
#include "config.h"
#include "encoder.h"
#include "menu.h"

U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, SCR_CS, SCR_DC, SCR_RES);
uint8_t needRedraw = 1;

void sreenRedraw()
{
    needRedraw = 1;
}

void screenSetup()
{
    u8g2.begin();
    mui.begin(u8g2, fds_data, muif_list, muif_list_count);
    mui.gotoForm(/* form_id= */ 1, /* initial_cursor_position= */ 0);
}

void screenLoop()
{

    u8g2.setFont(u8g2_font_helvR08_tr);
    if (mui.isFormActive())
    {
        if (needRedraw)
        {
            u8g2.firstPage();
            do
            {
                mui.draw();
            } while (u8g2.nextPage());
            needRedraw = 0;
        }
    }
    else
    {
        u8g2.firstPage();
        do
        {
            u8g2.setCursor(0, 20);
            u8g2.print(millis());
        } while (u8g2.nextPage());
    }
}