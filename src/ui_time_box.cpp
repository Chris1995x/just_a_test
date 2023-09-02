#include "ui_time_box.h"

Time_Box::Time_Box(
    U8G2_ST7920_128X64_F_SW_SPI *display, 
    time_s* time_to_draw, 
    std::string text,
    uint8_t x,
    uint8_t y,
    uint8_t width)
{
    m_u8g2 = display;
    m_time_to_draw = time_to_draw;

    m_current_time = new time_s();
    m_current_time->hour = 0;
    m_current_time->minute = 0;
    m_current_time->millisecond = 0;

    m_selected_digit = 0; // Einser, Zehner, Hunderter, Tausender
    m_text = text;
    m_x = x;
    m_y = y;
    m_width = width;
}

Time_Box::~Time_Box(void)
{
    delete m_current_time;
    m_current_time = nullptr;
}

void Time_Box::select_box()
{
    m_selected = true;
}

void Time_Box::drawScreenToBuffer(bool highlight)
{
    // If not selected -> update time with the provided time
    if(!m_selected) {
        m_current_time->hour = m_time_to_draw->hour;
        m_current_time->minute = m_time_to_draw->minute;
    }

    std::string text_to_print;
    char time_string[16];
    sprintf(time_string, "%dh:%dm", m_current_time->hour, m_current_time->minute);

    text_to_print += time_string;

    // Print the time with or without box
    if(m_selected) {
        m_u8g2->drawButtonUTF8(m_x, m_y, U8G2_BTN_BW2, m_width, 1, 1, text_to_print.c_str());
    }
    else if(highlight) {
        m_u8g2->drawButtonUTF8(m_x, m_y, U8G2_BTN_BW1, m_width, 1, 1, text_to_print.c_str());
    }
    else {
        m_u8g2->drawButtonUTF8(m_x, m_y, U8G2_BTN_BW0, m_width, 1, 1, text_to_print.c_str());
    }
}

void Time_Box::up()
{
    if(m_selected) {
        if(m_selected_digit > 2 /*True if hours are selected*/) {
            m_current_time->hour += pow(10, m_selected_digit - 2);
            // Verify that the selected hour is not bigger than 23
            m_current_time->hour = m_current_time->hour > 23 ? 0 : m_current_time->hour;
        }
        else {
            m_current_time->minute += pow(10, m_selected_digit);
            // Verify that the selected minute is not bigger than 59
            m_current_time->minute = m_current_time->minute > 59 ? 0 : m_current_time->minute;
        }
    }
}

void Time_Box::down()
{
    if(m_selected) {        
        if(m_selected_digit > 2 /*True if hours are selected*/) {
            m_current_time->hour -= pow(10, m_selected_digit - 2);
            // Verify that the selected hour is not smaller than 0
            m_current_time->hour = m_current_time->hour < 0 ? 23 : m_current_time->hour;
        }
        else {
            m_current_time->minute -= pow(10, m_selected_digit);
            // Verify that the selected minute is not samller than 0
            m_current_time->minute = m_current_time->minute < 0 ? 59 : m_current_time->minute;
        }}
}

void Time_Box::left()
{
    if(m_selected) {
        m_selected_digit++;
        // If m_selected_digit is bigger 3, set it back to 0
        // This is neccesary for the pow() function later on, so that 10^0 = 1
        m_selected_digit = m_selected_digit > MAX_DIGITS_IN_TIME - 1  ? 0 : m_selected_digit;
    }
}

void Time_Box::right()
{
    if(m_selected) {
        m_selected_digit--;
        // If m_selected_digit is smaller 0, set it back to 3
        m_selected_digit = m_selected_digit < 0 ? MAX_DIGITS_IN_TIME - 1 : m_selected_digit;
    }
}

time_s* Time_Box::select()
{
    m_selected = false;
    return m_current_time;
}

void Time_Box::back()
{
   m_selected = false;
}
