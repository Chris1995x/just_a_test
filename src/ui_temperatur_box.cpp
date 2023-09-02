#include "ui_temperatur_box.h"

Temperatur_Box::Temperatur_Box(
    U8G2_ST7920_128X64_F_SW_SPI *display, 
    int16_t* temperatur_to_draw, 
    std::string text,
    uint8_t x,
    uint8_t y,
    uint8_t width)
{
    m_u8g2 = display;
    m_temperatur_to_draw = temperatur_to_draw;
    m_current_temperatur = *temperatur_to_draw;
    m_selected_digit = 0; // Einser, Zehner, Hunderter, Tausender
    m_selected = false;
    m_text = text;
    m_x = x;
    m_y = y;
    m_width = width;
}

void Temperatur_Box::select_box()
{
    m_selected = true;
}

void Temperatur_Box::drawScreenToBuffer()
{
    // If not selected -> update temperatur with the provided temperature
    if(!m_selected) {
        m_current_temperatur = *m_temperatur_to_draw;
    }

    std::string text_to_print;
    char text_to_print_char[16];
    sprintf(text_to_print_char, "%d °C", m_current_temperatur);

    text_to_print += text_to_print_char;

    // Print the temperature with or without box
    if(m_selected) {
        m_u8g2->drawButtonUTF8(m_x, m_y, U8G2_BTN_BW1, m_width, 2, 2, text_to_print.c_str());
    }
    else {
        m_u8g2->drawButtonUTF8(m_x, m_y, U8G2_BTN_BW0, m_width, 2, 2, text_to_print.c_str());
    }
    
}

void Temperatur_Box::up()
{
    if(m_selected) {
        m_current_temperatur += pow(10, m_selected_digit);
    } 
}

void Temperatur_Box::down()
{
    if(m_selected) {
        m_current_temperatur -= pow(10, m_selected_digit);
    }
}

void Temperatur_Box::left()
{
    if(m_selected) {
        m_selected_digit++;
        // If m_selected_digit is bigger 3, set it back to 0
        // This is neccesary for the pow() function later on, so that 10^0 = 1
        m_selected_digit = m_selected_digit > MAX_DIGITS_FOR_TEMPERATUR - 1 ? 0 : m_selected_digit;
    }
}

void Temperatur_Box::right()
{   
    if(m_selected) {
        m_selected_digit--;
        // If m_selected_digit is smaller 0, set it back to 3
        m_selected_digit = m_selected_digit < 0 ? MAX_DIGITS_FOR_TEMPERATUR - 1 : m_selected_digit;
    }
}

int16_t Temperatur_Box::select()
{
    m_selected = true;
    return m_current_temperatur;   
}

void Temperatur_Box::back()
{
    m_selected = false;
}
