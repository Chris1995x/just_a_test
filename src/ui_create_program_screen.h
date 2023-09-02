#ifndef CREATE_PROGRAM_SCREEN_H
#define CREATE_PROGRAM_SCREEN_H

#include <list>
#include <U8g2lib.h>

#include "ui_screen_manager.h"
#include "ui_screen.h"

#include "ui_temperatur_box.h"
#include "ui_time_box.h"

class Create_Program_Screen : public Screen {
    public:
        Create_Program_Screen(U8G2_ST7920_128X64_F_SW_SPI* display, Screen_Manager* screen_manager);

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
            TARGET_TEMPERATUR_BOX,
            TIME_INTERVAL_BOX,
            NEXT_BUTTON,
            START_BUTTON
        };
        U8G2_ST7920_128X64_F_SW_SPI* m_u8g2;
        Screen_Manager* m_screen_manager;
        Temperatur_Box* m_target_temperatur_box;
        Time_Box* m_time_interval_box;
};

#endif