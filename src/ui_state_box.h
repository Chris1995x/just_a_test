#ifndef STATE_BOX_H
#define STATE_BOX_H

#include <U8g2lib.h>

class State_Box {
    public:
        State_Box(U8G2_ST7920_128X64_F_SW_SPI* display, uint8_t x, uint8_t y, uint8_t width);

    public:
        void drawScreenToBuffer(bool current_state);

    private:
        std::string m_text;
        U8G2_ST7920_128X64_F_SW_SPI* m_u8g2;
        uint8_t m_x;
        uint8_t m_y;
        uint8_t m_width;
};

#endif