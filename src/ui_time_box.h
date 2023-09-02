#ifndef TIME_BOX_H
#define TIME_BOX_H

#include <U8g2lib.h>

#include "system_state.h"

#define MAX_DIGITS_IN_TIME 4

class Time_Box {
    public:
        Time_Box(U8G2_ST7920_128X64_F_SW_SPI* display, time_s* time_to_draw, std::string text, uint8_t x, uint8_t y, uint8_t width);
        ~Time_Box(void);

    public:   
        void select_box();
        void drawScreenToBuffer();
        void up();
        void down();
        void left();
        void right();
        time_s* select();
        void back();
    
    private:
        U8G2_ST7920_128X64_F_SW_SPI* m_u8g2;
        time_s* m_time_to_draw;
        time_s* m_current_time;
        int8_t m_selected_digit;
        bool m_selected;
        std::string m_text;
        uint8_t m_x;
        uint8_t m_y;
        uint8_t m_width;
};

#endif