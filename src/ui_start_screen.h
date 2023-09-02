#ifndef START_SCREEN_H
#define START_SCREEN_H

#include <list>
#include <U8g2lib.h>

#include "ui_screen_manager.h"
#include "ui_screen.h"

class Start_Screen : public Screen {
    public:
        Start_Screen(U8G2_ST7920_128X64_F_SW_SPI* display, Screen_Manager* screen_manager);

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