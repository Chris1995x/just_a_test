#include "ui_running_program_screen.h"

Running_Program_Screen::Running_Program_Screen(U8G2_ST7920_128X64_F_SW_SPI* display, System_State* system_state, Screen_Manager* screen_manager)
{
    m_u8g2 = display;
    m_system_state = system_state;
    m_screen_manager = screen_manager;

    m_target_temperatur_box = new Temperatur_Box(m_u8g2, m_system_state->get_current_target_temperatur(), "Target Temp.: ", 0, 128, 32);
    m_current_temperatur_box = new Temperatur_Box(m_u8g2, m_system_state->get_current_temperature(), "Current Temp.: ", 32, 128, 32);
    m_time_interval_box = new Time_Box(m_u8g2, m_system_state->get_current_time(), "Time: ", 64, 128, 32);

    m_hold_button = new Button_Box(m_u8g2, "Hold", 0, 0, 64);
    m_stopp_button = new Button_Box(m_u8g2, "Stopp", 64, 0, 64);

    m_highlighted_box = NONE_SELECTED;
    m_selected_box = NONE_SELECTED;
}

Running_Program_Screen::~Running_Program_Screen()
{
    delete m_target_temperatur_box;
    m_target_temperatur_box = nullptr;

    delete m_current_temperatur_box;
    m_current_temperatur_box = nullptr;

    delete m_time_interval_box;
    m_time_interval_box = nullptr;

    delete m_hold_button;   
    m_hold_button = nullptr;

    delete m_stopp_button;
    m_stopp_button = nullptr;
}

void Running_Program_Screen::drawScreenToBuffer()
{
    m_target_temperatur_box->drawScreenToBuffer(m_system_state->get_current_target_temperatur(), false);
    m_current_temperatur_box->drawScreenToBuffer(m_system_state->get_current_temperature(), false);
    m_time_interval_box->drawScreenToBuffer(false);
    m_hold_button->drawButtonToBuffer(m_highlighted_box == HOLD_BUTTON);
    m_stopp_button->drawButtonToBuffer(m_highlighted_box == STOPP_BUTTON);
}

void Running_Program_Screen::up()
{
    // Do nothing
}

void Running_Program_Screen::down()
{
    // Do nothing
}

void Running_Program_Screen::left()
{
        switch (m_highlighted_box)
        {
            case NONE_SELECTED:
                m_selected_box = STOPP_BUTTON;
                break;
            case HOLD_BUTTON:
                // Do nothing
                break;
            case STOPP_BUTTON:
                m_selected_box = HOLD_BUTTON;
                break;
            default:
                break;
        }
}

void Running_Program_Screen::right()
{
        switch (m_highlighted_box)
        {
            case NONE_SELECTED:
                m_selected_box = HOLD_BUTTON;
                break;
            case HOLD_BUTTON:
                m_selected_box = STOPP_BUTTON;
            break;
            case STOPP_BUTTON:
                // Do nothing
                break;
            default:
                break;
        }
}

void Running_Program_Screen::select()
{
    switch (m_selected_box)
    {
        case HOLD_BUTTON:
            m_system_state->set_oven_state(OVEN_HOLD);
            break;
        case STOPP_BUTTON:
            m_system_state->set_oven_state(OVEN_OFF);
            m_screen_manager->setCurrentScreen(START_SCREEN);
            break;
        default:
            break;
    }
    
}

void Running_Program_Screen::back()
{
    // Do nothing
}