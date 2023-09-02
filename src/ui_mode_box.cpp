#include "ui_mode_box.h"

Mode_Box::Mode_Box(U8G2_ST7920_128X64_F_SW_SPI *display, uint8_t x, uint8_t y, uint8_t width)
{
    m_u8g2 = display;
    m_x = x;
    m_y = y;
    m_width = width;
    m_text = "Mode: ";
}

void Mode_Box::drawScreenToBuffer(Program_Point_Type current_type)
{
    std::string type_text = "";
    switch(current_type)
    {
        case HOLD_TEMPERATUR:
            type_text = "Hold";
            break;
        case RAMP_TEMPERATUR:
            type_text = "Ramp";
            break;
        case RAMP_TEMPERATUR_POINT:
            type_text = "Ramp";
            break;
    }
    std::string text_to_print = m_text + type_text;
    m_u8g2->drawButtonUTF8(m_x, m_y, U8G2_BTN_BW0, m_width, 1, 1, text_to_print.c_str());
}
