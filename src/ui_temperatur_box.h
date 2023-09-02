#ifndef TEMPERATUR_BOX_H
#define TEMPERATUR_BOX_H

#include <U8g2lib.h>

#include "system_state.h"

#define MAX_DIGITS_FOR_TEMPERATUR 4

class Temperatur_Box {
    public:
        Temperatur_Box(U8G2_ST7920_128X64_F_SW_SPI* display, int16_t temperatur_to_draw, std::string text, uint8_t x, uint8_t y, uint8_t width);

    public:
        void select_box();
        void drawScreenToBuffer(int16_t temperatur_to_draw);
        void up();
        void down();
        void left();
        void right();
        int16_t select();
        void back();
    
    private:
        U8G2_ST7920_128X64_F_SW_SPI* m_u8g2;
        int16_t m_temperatur_to_draw;
        int16_t m_current_temperatur;
        int8_t m_selected_digit;
        bool m_selected;
        std::string m_text;        
        uint8_t m_x;
        uint8_t m_y;
        uint8_t m_width;
};

#endif
