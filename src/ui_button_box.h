#ifndef BUTTON_BOX_H
#define BUTTON_BOX_H

#include <U8g2lib.h>

class Button_Box {
    public:
        Button_Box(U8G2_ST7920_128X64_F_SW_SPI* display, std::string button_text, uint8_t x, uint8_t y, uint8_t width);

    public:
        void drawButtonToBuffer(bool highlight);
        
    private:
        U8G2_ST7920_128X64_F_SW_SPI* m_u8g2;
        std::string m_button_text;
        uint8_t m_x;
        uint8_t m_y;
        uint8_t m_width;
};

#endif