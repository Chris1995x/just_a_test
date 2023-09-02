#ifndef CREATE_PROGRAM_SCREEN_H
#define CREATE_PROGRAM_SCREEN_H

#include <list>
#include <U8g2lib.h>

#include "ui_screen_manager.h"
#include "ui_screen.h"

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
        U8G2_ST7920_128X64_F_SW_SPI* m_u8g2;
        Screen_Manager* m_screen_manager;
};

#endif