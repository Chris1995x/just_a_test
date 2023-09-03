#ifndef RUNNING_PROGRAM_SCREEN_H
#define RUNNING_PROGRAM_SCREEN_H

#include <list>
#include <U8g2lib.h>

#include "system_state.h"
#include "ui_screen_manager.h"
#include "ui_screen.h"
#include "ui_temperatur_box.h"
#include "ui_time_box.h"
#include "ui_button_box.h"

class Running_Program_Screen : public Screen {
    public:
        Running_Program_Screen(U8G2_ST7920_128X64_F_SW_SPI* display, System_State* system_state, Screen_Manager* screen_manager);
        ~Running_Program_Screen();

        public:
            void drawScreenToBuffer();
            void up();
            void down();
            void left();
            void right();
            void select();
            void back();

    private:
        enum Available_Boxes {
            NONE_SELECTED,
            HOLD_BUTTON,
            STOPP_BUTTON
        };
        U8G2_ST7920_128X64_F_SW_SPI* m_u8g2;
        System_State* m_system_state;
        Screen_Manager* m_screen_manager;
        Temperatur_Box* m_target_temperatur_box;
        Temperatur_Box* m_current_temperatur_box;
        Time_Box* m_time_interval_box;
        Button_Box* m_hold_button;
        Button_Box* m_stopp_button;
        Available_Boxes m_highlighted_box;
        Available_Boxes m_selected_box;
};

#endif