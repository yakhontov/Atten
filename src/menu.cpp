#include <Arduino.h>
#include <U8g2lib.h>
#include <MUIU8g2.h>
#include "menu.h"

uint8_t mui_hrule(mui_t *ui, uint8_t msg)
{
  u8g2_t *u8g2 = mui_get_U8g2(ui);
  switch(msg)
  {
    case MUIF_MSG_DRAW:
      u8g2_DrawHLine(u8g2, 0, mui_get_y(ui), u8g2_GetDisplayWidth(u8g2));
      break;
  }
  return 0;
}

muif_t muif_list[] = { // MUI Field Processing Function. Обработчики для рисования каждого элемента формы. Элемент и обработчик связываются по двухбуквенному индексу, если таковой присутствует в FDS
  MUIF_U8G2_FONT_STYLE(0, u8g2_font_helvR08_tr),        // regular font // Ситль для MUI_STYLE(0)
  MUIF_U8G2_FONT_STYLE(1, u8g2_font_helvB08_tr),        // bold font // Стиль для MUI_STYLE(1)
  MUIF_RO("HR", mui_hrule), // Обработчик для рисования горизонтальной линии
  MUIF_U8G2_LABEL() // Стандартный обработчик для лэйбла
};
//  MUIF_RO("GP",mui_u8g2_goto_data), //
//   MUIF_BUTTON("GC", mui_u8g2_goto_form_w1_pi),

//   MUIF_U8G2_U8_MIN_MAX("NV", &num_value, 0, 99, mui_u8g2_u8_min_max_wm_mud_pi),
//   MUIF_U8G2_U8_MIN_MAX_STEP("NB", &bar_value, 0, 16, 1, MUI_MMS_2X_BAR, mui_u8g2_u8_bar_wm_mud_pf),
//   MUIF_U8G2_U16_LIST("NA", &animal_idx, NULL, animal_name_list_get_str, animal_name_list_get_cnt, mui_u8g2_u16_list_line_wa_mud_pi),

//   // register custom function to show the data 
//   MUIF_RO("SH", show_my_data), 

//   // a button for the menu... 
//   //MUIF_BUTTON("GO", mui_u8g2_btn_goto_wm_fi)  
//   MUIF_EXECUTE_ON_SELECT_BUTTON("GO", mui_u8g2_btn_goto_wm_fi)  
//};

const int muif_list_count = sizeof(muif_list)/sizeof(muif_t);

fds_t fds_data[] = // Form Definition String. Строка, содержащая описание всех форм интерфейса. Строка формируется при помощи макросов:
MUI_FORM(1) // Индекс формы. Произвольное число от 1 до 255
MUI_STYLE(1) // Стиль (шрифт) следующих элементов. Сам стиль под этим же индексом описывается в muif_list
MUI_LABEL(5, 8, "Parameters") // Лейбл. Заголовок формы
MUI_STYLE(0) // Стиль (шрифт) следующих элементов. Сам стиль под этим же индексом описывается в muif_list
MUI_XY("HR", 0, 11) // Кастомный элемент формы с индексом "HR" (произвольных два символа), в который могут быть переданы координаты X, Y. Функция отрисовки элемента описана в muif_list
//MUI_DATA("GP", MUI_10 "Enter Data|" MUI_12 "Show Data")
// MUI_XYA("GC", 5, 24, 0)
// MUI_XYA("GC", 10, 36, 1)
// MUI_XYA("GC", 15, 48, 1)
;

