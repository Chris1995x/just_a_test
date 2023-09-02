#ifndef UI_H
#define UI_H

#include <U8g2lib.h>
#include <map>

#include "system_state.h"
#include "ui_screen_manager.h"
#include "ui_screen.h"
#include "ui_start_screen.h"
#include "ui_create_program_screen.h"
#include "ui_running_program_screen.h"

class UI {
  public:
    UI(U8G2_ST7920_128X64_F_SW_SPI* display, System_State* system_state);
    ~UI(void);

  public:
    void initialize();
    void drawUI();    

  private:
    U8G2_ST7920_128X64_F_SW_SPI* m_u8g2;
    System_State* m_system_state;
    Screen_Manager* m_screen_manager;
    std::map<Screen_Type, Screen*>* m_screens;
};

#endif