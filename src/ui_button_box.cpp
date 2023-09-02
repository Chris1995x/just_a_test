#include "ui_button_box.h"

Button_Box::Button_Box(U8G2_ST7920_128X64_F_SW_SPI *display, std::string button_text, uint8_t x, uint8_t y, uint8_t width)
{
    m_u8g2 = display;
    m_button_text = button_text;
    m_x = x;
    m_y = y;
    m_width = width;
}

void Button_Box::drawButtonToBuffer(bool highlight)
{
    if (highlight)
    {
         m_u8g2->drawButtonUTF8(m_x, m_y, U8G2_BTN_BW1, m_width, 1, 1, m_button_text.c_str());
    } else {
         m_u8g2->drawButtonUTF8(m_x, m_y, U8G2_BTN_BW0, m_width, 1, 1, m_button_text.c_str());
    }
}
