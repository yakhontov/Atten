#include <Arduino.h>
#include <U8g2lib.h>
#include <MUIU8g2.h>
#include "config.h"
#include "main.h"
#include "menu.h"


// https://github.com/olikraus/u8g2/blob/master/sys/arduino/u8g2_page_buffer/MUIInputVersatileRotaryEncoder/MUIInputVersatileRotaryEncoder.ino

// Pics creation:
// https://onlinepngtools.com/create-monochrome-png
// https://javl.github.io/image2cpp/


U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, SCR_CS, SCR_DC, SCR_RES);
MUIU8G2 mui;

void setup(void) {
  EnableEnc();
  u8g2.begin(/* menu_select_pin= */ ENC_SW, /* menu_next_pin= */ 4, /* menu_prev_pin= */ 2, /* menu_up_pin= */ U8X8_PIN_NONE, /* menu_down_pin= */ U8X8_PIN_NONE, /* menu_home_pin= */ 3);  
  mui.begin(u8g2, fds_data, muif_list, muif_list_count);
  mui.gotoForm(/* form_id= */ 1, /* initial_cursor_position= */ 0);
}

uint8_t is_redraw = 1;
void loop(void) {
  u8g2.setFont(u8g2_font_helvR08_tr);
  if ( mui.isFormActive() )
  {
    /* menu is active: draw the menu */
    if ( is_redraw ) {
      u8g2.firstPage();
      do {
          mui.draw();
      } while( u8g2.nextPage() );
      is_redraw = 0;
    }
    /* handle events */
    switch(u8g2.getMenuEvent()) {
      case U8X8_MSG_GPIO_MENU_SELECT:
        mui.sendSelect();
        is_redraw = 1;
        break;
    }
  } else {  
    /* menu not active: show something else */
    u8g2.firstPage();
    do {
        u8g2.setCursor(0,20);
        u8g2.print(millis());
    } while( u8g2.nextPage() );
  } /* mui.isFormActive() */
} /* loop */