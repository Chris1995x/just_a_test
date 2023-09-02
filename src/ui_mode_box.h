#ifndef MODE_BOX_H
#define MODE_BOX_H

#include <U8g2lib.h>

#include "system_state.h"

class Mode_Box {
    public:
        Mode_Box(U8G2_ST7920_128X64_F_SW_SPI *display, uint8_t x, uint8_t y, uint8_t width);
    
    public:
        void drawScreenToBuffer(Program_Point_Type current_type);

    private:
        U8G2_ST7920_128X64_F_SW_SPI* m_u8g2;
        uint8_t m_x;
        uint8_t m_y;
        uint8_t m_width;
        std::string m_text;
};

#endif