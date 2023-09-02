#include "ui_create_program_screen.h"

Create_Program_Screen::Create_Program_Screen(U8G2_ST7920_128X64_F_SW_SPI* display, System_State* system_state , Screen_Manager* screen_manager) {
    m_u8g2 = display;
    m_system_state = system_state;
    m_screen_manager = screen_manager;

    m_target_temperatur_box = new Temperatur_Box(m_u8g2, m_system_state->get_current_target_temperatur(), "Target Temp.: ", 0, 128, 32);
    m_time_interval_box = new Time_Box(m_u8g2, m_system_state->get_current_time(), "Hold for: ", 32, 128, 32);
    m_mode_box = new Mode_Box(m_u8g2, 64, 128, 32);
    m_next_button = new Button_Box(m_u8g2, "Next", 0, 0, 64);
    m_start_button = new Button_Box(m_u8g2, "Start", 64, 0, 64);

    m_highlighted_box = TARGET_TEMPERATUR_BOX;
    m_selected_box = NONE_SELECTED;
}

Create_Program_Screen::~Create_Program_Screen()
{
    delete m_target_temperatur_box;
    m_target_temperatur_box = nullptr;

    delete m_time_interval_box;
    m_time_interval_box = nullptr;

    delete m_mode_box;
    m_mode_box = nullptr;

    delete m_next_button;
    m_next_button = nullptr;

    delete m_start_button;
    m_start_button = nullptr;
}

void Create_Program_Screen::drawScreenToBuffer()
{
}

void Create_Program_Screen::up()
{
}

void Create_Program_Screen::down()
{
}

void Create_Program_Screen::left()
{
}

void Create_Program_Screen::right()
{
}

void Create_Program_Screen::select()
{
}

void Create_Program_Screen::back()
{
}
