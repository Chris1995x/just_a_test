#ifndef CREATE_PROGRAM_SCREEN_H
#define CREATE_PROGRAM_SCREEN_H

#include <list>
#include <U8g2lib.h>

#include "system_state.h"
#include "ui_screen_manager.h"
#include "ui_screen.h"

#include "ui_temperatur_box.h"
#include "ui_time_box.h"
#include "ui_mode_box.h"
#include "ui_button_box.h"

class Create_Program_Screen : public Screen {
    public:
        Create_Program_Screen(U8G2_ST7920_128X64_F_SW_SPI* display, System_State* system_state , Screen_Manager* screen_manager);
        ~Create_Program_Screen();

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
            TARGET_TEMPERATUR_BOX,
            TIME_INTERVAL_BOX,
            NEXT_BUTTON,
            START_BUTTON
        };
        U8G2_ST7920_128X64_F_SW_SPI* m_u8g2;
        System_State* m_system_state;
        Screen_Manager* m_screen_manager;
        Temperatur_Box* m_target_temperatur_box;
        Time_Box* m_time_interval_box;
        Mode_Box* m_mode_box;
        Button_Box* m_next_button;
        Button_Box* m_start_button;
        Available_Boxes m_highlighted_box;
        Available_Boxes m_selected_box;
};

#endif