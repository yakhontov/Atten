#include <Arduino.h>
#include <U8g2lib.h>
#include <MUIU8g2.h>

/*
  list of animal names
*/
const char *animals[] = { "Bird", "Bison", "Cat", "Crow", "Dog", "Elephant", "Fish", "Gnu", "Horse", "Koala", "Lion", "Mouse", "Owl", "Rabbit", "Spider", "Turtle", "Zebra" };


uint8_t num_value = 0;
uint8_t bar_value = 0;
uint16_t animal_idx = 0;



uint8_t mui_hrule(mui_t *ui, uint8_t msg);
uint8_t show_my_data(mui_t *ui, uint8_t msg);
uint16_t animal_name_list_get_cnt(void *data);
const char *animal_name_list_get_str(void *data, uint16_t index);

muif_t muif_list[] = { // Обработчики для рисования каждого элемента формы. Элемент и обработчик связываются по двухбуквенному индексу
  MUIF_U8G2_FONT_STYLE(0, u8g2_font_helvR08_tr),        // regular font // Ситль для MUI_STYLE(0)
  MUIF_U8G2_FONT_STYLE(1, u8g2_font_helvB08_tr),        // bold font // Стиль для MUI_STYLE(1)

  MUIF_RO("HR", mui_hrule), // Обработчик для рисования горизонтальной линии
  MUIF_U8G2_LABEL(), // Стандартный обработчик для Лэйбла
  MUIF_RO("GP",mui_u8g2_goto_data), //
  MUIF_BUTTON("GC", mui_u8g2_goto_form_w1_pi),

  MUIF_U8G2_U8_MIN_MAX("NV", &num_value, 0, 99, mui_u8g2_u8_min_max_wm_mud_pi),
  MUIF_U8G2_U8_MIN_MAX_STEP("NB", &bar_value, 0, 16, 1, MUI_MMS_2X_BAR, mui_u8g2_u8_bar_wm_mud_pf),
  MUIF_U8G2_U16_LIST("NA", &animal_idx, NULL, animal_name_list_get_str, animal_name_list_get_cnt, mui_u8g2_u16_list_line_wa_mud_pi),

  // register custom function to show the data 
  MUIF_RO("SH", show_my_data), 

  // a button for the menu... 
  //MUIF_BUTTON("GO", mui_u8g2_btn_goto_wm_fi)  
  MUIF_EXECUTE_ON_SELECT_BUTTON("GO", mui_u8g2_btn_goto_wm_fi)  
};


fds_t fds_data[] = 

MUI_FORM(1) // Индекс формы. Произвольное число от 1 до 255
MUI_STYLE(1) // Стиль (шрифт) следующих элементов. Сам стиль под этим же индексом описывается в muif_list
MUI_LABEL(5, 8, "VersatileRotaryEncoder") // Лейбл. Заголовок формы
MUI_STYLE(0) // Стиль (шрифт) следующих элементов. Сам стиль под этим же индексом описывается в muif_list
MUI_XY("HR", 0,11) // Кастомный элемент формы (горизонтальная линия). "HR" - произвольный индекс из двух символов. Элемент и функция его отрисовки описана в muif_list
MUI_DATA("GP", 
    MUI_10 "Enter Data|"
    MUI_12 "Show Data|"
    MUI_14 "Bileberda")
MUI_XYA("GC", 5, 24, 0) 
MUI_XYA("GC", 10, 36, 1) 
MUI_XYA("GC", 15, 48, 1) 

MUI_FORM(10)
MUI_STYLE(1)
MUI_LABEL(5, 8, "Enter Data")
MUI_XY("HR", 0,11)
MUI_STYLE(0)
MUI_LABEL(5,23, "Num:")
MUI_LABEL(5,36, "Bar:")
MUI_LABEL(5,49, "Animal:")
MUI_XY("NV", 50, 23)
MUI_XY("NB", 50, 36)
MUI_XYA("NA", 50, 49, 44)
MUI_XYAT("GO", 114, 60, 1, " Ok ") 

MUI_FORM(12)
MUI_STYLE(1)
MUI_LABEL(5, 8, "Show Data")
MUI_XY("HR", 0,11)
MUI_STYLE(0)
MUI_XY("SH", 0, 23)
MUI_XYAT("GO", 114, 60, 1, " Ok ") 
;


/*
muif_t muif_list[] = {
  MUIF_U8G2_FONT_STYLE(0, u8g2_font_helvR08_tr),        // regular font 
  MUIF_U8G2_FONT_STYLE(1, u8g2_font_helvB08_tr),        // bold font 

  MUIF_RO("HR", mui_hrule),
  MUIF_U8G2_LABEL(),
  MUIF_RO("GP",mui_u8g2_goto_data),  
  MUIF_BUTTON("GC", mui_u8g2_goto_form_w1_pi),

  MUIF_U8G2_U8_MIN_MAX("NV", &num_value, 0, 99, mui_u8g2_u8_min_max_wm_mud_pi),
  MUIF_U8G2_U8_MIN_MAX_STEP("NB", &bar_value, 0, 16, 1, MUI_MMS_2X_BAR, mui_u8g2_u8_bar_wm_mud_pf),
  MUIF_U8G2_U16_LIST("NA", &animal_idx, NULL, animal_name_list_get_str, animal_name_list_get_cnt, mui_u8g2_u16_list_line_wa_mud_pi),

  // register custom function to show the data 
  MUIF_RO("SH", show_my_data), 

  // a button for the menu... 
  //MUIF_BUTTON("GO", mui_u8g2_btn_goto_wm_fi)  
  MUIF_EXECUTE_ON_SELECT_BUTTON("GO", mui_u8g2_btn_goto_wm_fi)  
};


fds_t fds_data[] = 

MUI_FORM(1) // Индекс формы. Произвольное число от 1 до 255
MUI_STYLE(1) // Стиль (шрифт) следующих элементов. Сам стиль под этим же индексом описывается в muif_list
MUI_LABEL(5, 8, "VersatileRotaryEncoder") // Лейбл. Заголовок формы
MUI_STYLE(0) // Стиль (шрифт) следующих элементов. Сам стиль под этим же индексом описывается в muif_list
MUI_XY("HR", 0,11) // Кастомный элемент формы (горизонтальная линия). "HR" - произвольный индекс из двух символов. Элемент и функция его отрисовки описана в muif_list
MUI_DATA("GP", 
    MUI_10 "Enter Data|"
    MUI_12 "Show Data")
MUI_XYA("GC", 5, 24, 0) 
MUI_XYA("GC", 5, 36, 1) 

MUI_FORM(10)
MUI_STYLE(1)
MUI_LABEL(5, 8, "Enter Data")
MUI_XY("HR", 0,11)
MUI_STYLE(0)
MUI_LABEL(5,23, "Num:")
MUI_LABEL(5,36, "Bar:")
MUI_LABEL(5,49, "Animal:")
MUI_XY("NV", 50, 23)
MUI_XY("NB", 50, 36)
MUI_XYA("NA", 50, 49, 44)
MUI_XYAT("GO", 114, 60, 1, " Ok ") 

MUI_FORM(12)
MUI_STYLE(1)
MUI_LABEL(5, 8, "Show Data")
MUI_XY("HR", 0,11)
MUI_STYLE(0)
MUI_XY("SH", 0, 23)
MUI_XYAT("GO", 114, 60, 1, " Ok ") 
;
*/