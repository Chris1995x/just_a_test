#include "ui_create_program_screen.h"

Create_Program_Screen::Create_Program_Screen(U8G2_ST7920_128X64_F_SW_SPI* display, System_State* system_state , Screen_Manager* screen_manager) {
    m_u8g2 = display;
    m_system_state = system_state;
    m_screen_manager = screen_manager;

    resetTimeAndTemperature();

    m_target_temperatur_box = new Temperatur_Box(m_u8g2, m_configured_temperatur, "Target Temp.: ", 0, 128, 32);
    m_time_interval_box = new Time_Box(m_u8g2, m_configured_time, "Hold for: ", 32, 128, 32);
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

    delete m_configured_time;
    m_configured_time = nullptr;
}

void Create_Program_Screen::drawScreenToBuffer()
{
    m_target_temperatur_box->drawScreenToBuffer(m_configured_temperatur, m_highlighted_box == TARGET_TEMPERATUR_BOX);
    m_time_interval_box->drawScreenToBuffer(m_highlighted_box == TIME_INTERVAL_BOX);
    m_mode_box->drawScreenToBuffer(HOLD_TEMPERATUR);
    m_next_button->drawButtonToBuffer(m_highlighted_box == NEXT_BUTTON);
    m_start_button->drawButtonToBuffer(m_highlighted_box == START_BUTTON);
}

void Create_Program_Screen::up()
{
    if(m_selected_box == TARGET_TEMPERATUR_BOX) {
        m_target_temperatur_box->up();
    } else if(m_selected_box == TIME_INTERVAL_BOX) {
        m_time_interval_box->up();
    } else {
        switch (m_highlighted_box)
        {
        case TARGET_TEMPERATUR_BOX:
            m_selected_box = NEXT_BUTTON;
            break;
        case TIME_INTERVAL_BOX:
            m_selected_box = TARGET_TEMPERATUR_BOX;
            break;
        case NEXT_BUTTON:
            m_selected_box = TIME_INTERVAL_BOX;
            break;
        case START_BUTTON:
            m_selected_box = TIME_INTERVAL_BOX;
            break;
        default:
            break;
        }
    }
}

void Create_Program_Screen::down()
{
    if(m_selected_box == TARGET_TEMPERATUR_BOX) {
        m_target_temperatur_box->down();
    } else if(m_selected_box == TIME_INTERVAL_BOX) {
        m_time_interval_box->down();
    } else {
    switch (m_highlighted_box)
    {
        case TARGET_TEMPERATUR_BOX:
            m_selected_box = TIME_INTERVAL_BOX;
            break;
        case TIME_INTERVAL_BOX:
            m_selected_box = NEXT_BUTTON;
            break;
        case NEXT_BUTTON:
            m_selected_box = TARGET_TEMPERATUR_BOX;
            break;
        case START_BUTTON:  
            m_selected_box = TARGET_TEMPERATUR_BOX;
            break;
        default:
            break;
    }
    }
}

void Create_Program_Screen::left()
{
    if(m_selected_box == TARGET_TEMPERATUR_BOX) {
        m_target_temperatur_box->left();
    } else if(m_selected_box == TIME_INTERVAL_BOX) {
        m_time_interval_box->left();
    } else {
        switch (m_highlighted_box)
        {
            case TARGET_TEMPERATUR_BOX:
                // Do nothing
                break;
            case TIME_INTERVAL_BOX:
                // Do nothing
                break;
            case NEXT_BUTTON:
                // Do nothing
                break;
            case START_BUTTON:
                m_highlighted_box = NEXT_BUTTON;
                break;
            default:
                break;
        }
    }
}

void Create_Program_Screen::right()
{
    if(m_selected_box == TARGET_TEMPERATUR_BOX) {
        m_target_temperatur_box->right();
    } else if(m_selected_box == TIME_INTERVAL_BOX) {
        m_time_interval_box->right();
    } else {
        switch (m_highlighted_box)
        {
            case TARGET_TEMPERATUR_BOX:
                // Do nothing
                break;
            case TIME_INTERVAL_BOX:
                // Do nothing
                break;
            case NEXT_BUTTON:
                m_highlighted_box = START_BUTTON;
                break;
            case START_BUTTON:
                // Do nothing
                break;
            default:
                break;
    }}

}

void Create_Program_Screen::select()
{
    if(m_selected_box == TARGET_TEMPERATUR_BOX) {
        m_configured_temperatur = m_target_temperatur_box->select();
    } else if(m_selected_box == TIME_INTERVAL_BOX) {
        m_time_interval_box->select();
    } else {
        switch(m_highlighted_box)
        {
            case TARGET_TEMPERATUR_BOX:
                m_selected_box = TARGET_TEMPERATUR_BOX;
                break;
            case TIME_INTERVAL_BOX:
                m_selected_box = TIME_INTERVAL_BOX;
                break;
            case NEXT_BUTTON:
                m_highlighted_box = TARGET_TEMPERATUR_BOX;
                m_system_state->add_program_point(m_configured_temperatur, m_configured_time, HOLD_TEMPERATUR);
                resetTimeAndTemperature();
                break;
            case START_BUTTON:
                m_highlighted_box = TARGET_TEMPERATUR_BOX;
                m_system_state->add_program_point(m_configured_temperatur, m_configured_time, HOLD_TEMPERATUR);
                resetTimeAndTemperature();
                m_screen_manager->setCurrentScreen(RUN_PROGRAM_SCREEN);
                break;
            default:
                break;
        }
    }
}

void Create_Program_Screen::back()
{
    m_selected_box = NONE_SELECTED;
}

void Create_Program_Screen::resetTimeAndTemperature()
{
    m_configured_time = new time_s();
    m_configured_time->hour = 0;
    m_configured_time->minute = 0;
    m_configured_temperatur = 20;
}
