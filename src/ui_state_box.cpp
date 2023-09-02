#include "ui_state_box.h"

State_Box::State_Box(U8G2_ST7920_128X64_F_SW_SPI *display, uint8_t x, uint8_t y, uint8_t width)
{
    m_u8g2 = display;
    m_x = x;
    m_y = y;
    m_width = width;
    m_text = "Current State: ";
}

void State_Box::drawScreenToBuffer(bool current_state)
{
    std::string state_text = current_state ? "Heating" : "Cooling";
    std::string text_to_print = state_text + m_text;
    m_u8g2->drawButtonUTF8(m_x, m_y, U8G2_BTN_BW0, m_width, 1, 1, text_to_print.c_str());
}
