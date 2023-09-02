#include "ui_start_screen.h"

Start_Screen::Start_Screen(U8G2_ST7920_128X64_F_SW_SPI* display, System_State* system_state, Screen_Manager* screen_manager)
{
    m_u8g2 = display;
    m_system_state = system_state;
    m_screen_manager = screen_manager;

    m_target_temperatur_box = new Temperatur_Box(m_u8g2, m_system_state->get_current_target_temperatur(), "Target Temp. ", 0, 128, 32);
    m_current_temperatur_box = new Temperatur_Box(m_u8g2, m_system_state->get_current_temperature(), "Current Temp. ", 32, 128, 32);
    m_state_box = new State_Box(m_u8g2, 64, 128, 32);

    m_highlighted_box = TARGET_TEMPERATUR_BOX;
}

Start_Screen::~Start_Screen()
{
    delete m_target_temperatur_box;
    m_target_temperatur_box = nullptr;

    delete m_current_temperatur_box;
    m_current_temperatur_box = nullptr;

    delete m_state_box;
    m_state_box = nullptr;
}

void Start_Screen::drawScreenToBuffer()
{
    m_target_temperatur_box->drawScreenToBuffer(m_system_state->get_current_target_temperatur());
    m_current_temperatur_box->drawScreenToBuffer(m_system_state->get_current_temperature());
    drawToggleButton();
    drawProgramButton();
}

void Start_Screen::up()
{
    switch(m_highlighted_box)
    {
        case TARGET_TEMPERATUR_BOX:
            m_highlighted_box = PROGRAM_BUTTON;
            break;
        case TOGGLE_BUTTON:
            m_highlighted_box = TARGET_TEMPERATUR_BOX;
            break;
        case PROGRAM_BUTTON:
            m_highlighted_box = TOGGLE_BUTTON;
            break;
        default:
            // Do nothing
            break;
    }
}

void Start_Screen::down()
{
    switch (m_highlighted_box)
    {
    case TARGET_TEMPERATUR_BOX:
        m_highlighted_box = TOGGLE_BUTTON;
        break;
    case TOGGLE_BUTTON:
        m_highlighted_box = PROGRAM_BUTTON;
        break;
    case PROGRAM_BUTTON:
        m_highlighted_box = TARGET_TEMPERATUR_BOX;
        break;
    default:
        // Do nothing
        break;
    }
}

void Start_Screen::left()
{
    switch (m_highlighted_box)
    {
    case PROGRAM_BUTTON:
        m_highlighted_box = TOGGLE_BUTTON;
        break;
    default:
        // Do nothing
        break;
    }
}

void Start_Screen::right()
{
    switch (m_highlighted_box)
    {
    case TOGGLE_BUTTON:
        m_highlighted_box = PROGRAM_BUTTON;
        break;
    default:
        // Do nothing
        break;
    }
}

void Start_Screen::select()
{
}

void Start_Screen::back()
{
}

// Toggle button is box 2
void Start_Screen::drawToggleButton()
{
    m_u8g2->drawButtonUTF8(0, 0, U8G2_BTN_BW0, 0, 2, 2, "On / Off");
}

// Program button is box 3
void Start_Screen::drawProgramButton()
{
    m_u8g2->drawButtonUTF8(0, 0, U8G2_BTN_BW0, 0, 2, 2, "Program");
}
