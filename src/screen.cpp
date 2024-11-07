#include "screen.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include <MUIU8g2.h>
#include "config.h"
#include "encoder.h"
#include "menu.h"

U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, SCR_CS, SCR_DC, SCR_RES);

void screenSetup()
{
    u8g2.begin();
    mui.begin(u8g2, fds_data, muif_list, muif_list_count);
    mui.gotoForm(/* form_id= */ 1, /* initial_cursor_position= */ 0);
}

void screenLoop()
{
    static uint8_t is_redraw = 1;

    u8g2.setFont(u8g2_font_helvR08_tr);
    if (mui.isFormActive()) {
        /* menu is active: draw the menu */
        if (is_redraw) {
            u8g2.firstPage();
            do {
                mui.draw();
            } while (u8g2.nextPage());
            is_redraw = 0;
        }
        /* handle events */
        switch (u8g2.getMenuEvent()) {
        case U8X8_MSG_GPIO_MENU_SELECT:
            mui.sendSelect();
            is_redraw = 1;
            break;
        }
    } else {
        /* menu not active: show something else */
        u8g2.firstPage();
        do {
            u8g2.setCursor(0, 20);
            u8g2.print(millis());
        } while (u8g2.nextPage());
    }
}