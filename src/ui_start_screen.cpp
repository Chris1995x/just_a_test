#include "ui_start_screen.h"

Start_Screen::Start_Screen(U8G2_ST7920_128X64_F_SW_SPI* display, System_State* system_state, Screen_Manager* screen_manager) {
    m_u8g2 = display;
    m_system_state = system_state;
    m_screen_manager = screen_manager;

    m_target_temperatur_box = new Temperatur_Box(m_u8g2, m_system_state->get_current_target_temperatur(), "Target Temp. ", 0, 128, 32);
    m_current_temperatur_box = new Temperatur_Box(m_u8g2, m_system_state->get_current_temperature(), "Current Temp. ", 32, 128, 32);
    m_state_box = new State_Box(m_u8g2, 64, 128, 32);
    m_toggle_button = new Button_Box(m_u8g2, "On / Off", 0, 0, 64);
    m_program_button = new Button_Box(m_u8g2, "Program", 64, 0, 64);

    m_highlighted_box = TARGET_TEMPERATUR_BOX;
    m_selected_box = NONE_SELECTED;
}

Start_Screen::~Start_Screen()
{
    delete m_target_temperatur_box;
    m_target_temperatur_box = nullptr;

    delete m_current_temperatur_box;
    m_current_temperatur_box = nullptr;

    delete m_state_box;
    m_state_box = nullptr;

    delete m_toggle_button;
    m_toggle_button = nullptr;

    delete m_program_button;
    m_program_button = nullptr;
}

void Start_Screen::drawScreenToBuffer()
{
    m_target_temperatur_box->drawScreenToBuffer(m_system_state->get_current_target_temperatur(), m_highlighted_box == TARGET_TEMPERATUR_BOX);
    m_current_temperatur_box->drawScreenToBuffer(m_system_state->get_current_temperature(), false);
    m_state_box->drawScreenToBuffer(m_system_state->get_oven_state());
    m_toggle_button->drawButtonToBuffer(m_highlighted_box == TOGGLE_BUTTON);
    m_program_button->drawButtonToBuffer(m_highlighted_box == PROGRAM_BUTTON);
}

void Start_Screen::up()
{
    if(m_selected_box == TARGET_TEMPERATUR_BOX) {
        m_target_temperatur_box->up();
    } else {
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
}

void Start_Screen::down()
{
    if(m_selected_box == TARGET_TEMPERATUR_BOX) {
        m_target_temperatur_box->down();
    } else {
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
}

void Start_Screen::left()
{
    if(m_selected_box == TARGET_TEMPERATUR_BOX) {
        m_target_temperatur_box->left();
    } else {
        switch (m_highlighted_box)
        {
            case TARGET_TEMPERATUR_BOX:
                // Do nothing
                break;
            case TOGGLE_BUTTON:
                // Do nothing
                break;
            case PROGRAM_BUTTON:
                m_highlighted_box = TOGGLE_BUTTON;
                break;
            default:
                // Do nothing
                break;
        }
    }
}

void Start_Screen::right()
{
    if(m_selected_box == TARGET_TEMPERATUR_BOX) {
        m_target_temperatur_box->right();
    } else {
        switch (m_highlighted_box)
        {
            case TARGET_TEMPERATUR_BOX:
                // Do nothing
                break;
            case TOGGLE_BUTTON:
                m_highlighted_box = PROGRAM_BUTTON;
                break;
            case PROGRAM_BUTTON:
                // Do nothing
                break;
            default:
                // Do nothing
                break;
        }
    }
}

void Start_Screen::select()
{
    if(m_selected_box == TARGET_TEMPERATUR_BOX) {
        m_system_state->set_current_target_temperature(m_target_temperatur_box->select());
        m_selected_box = NONE_SELECTED;
    } else {
        switch (m_highlighted_box)
        {
            case TOGGLE_BUTTON:
            {
                switch(m_system_state->get_oven_state())
                {
                    case OVEN_OFF:
                        m_system_state->set_oven_state(OVEN_ON);
                        break;
                    case OVEN_ON:
                       m_system_state->set_oven_state(OVEN_OFF);
                        break;
                    default:
                        m_system_state->set_oven_state(OVEN_ERROR);
                        break;
                }
            } break;
            case PROGRAM_BUTTON:
            {
                m_highlighted_box = TARGET_TEMPERATUR_BOX;
                m_screen_manager->setCurrentScreen(CREATE_PROGRAM_SCREEN); 
            } break;
            case TARGET_TEMPERATUR_BOX:
            {
                m_selected_box = TARGET_TEMPERATUR_BOX;
                m_target_temperatur_box->select_box(); 
            } break;
        
            default:
                break;
        }
    }
}

void Start_Screen::back()
{
    if(m_selected_box == TARGET_TEMPERATUR_BOX) {
        m_target_temperatur_box->back();
    }
    m_selected_box = NONE_SELECTED;
}