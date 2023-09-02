#include "ui_start_screen.h"

Start_Screen::Start_Screen(U8G2_ST7920_128X64_F_SW_SPI *display, Screen_Manager *screen_manager)
{
    m_u8g2 = display;
    m_screen_manager = screen_manager;
}

void Start_Screen::drawScreenToBuffer()
{
}

void Start_Screen::up()
{
}

void Start_Screen::down()
{
}

void Start_Screen::left()
{
}

void Start_Screen::right()
{
}

void Start_Screen::select()
{
}

void Start_Screen::back()
{
}
