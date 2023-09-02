#include "ui_running_program_screen.h"

Running_Program_Screen::Running_Program_Screen(U8G2_ST7920_128X64_F_SW_SPI *display, Screen_Manager *screen_manager)
{
    m_u8g2 = display;
    m_screen_manager = screen_manager;
}

void Running_Program_Screen::up()
{
}

void Running_Program_Screen::down()
{
}

void Running_Program_Screen::left()
{
}

void Running_Program_Screen::right()
{
}

void Running_Program_Screen::select()
{
}

void Running_Program_Screen::back()
{
}

void Running_Program_Screen::drawScreenToBuffer()
{
}
