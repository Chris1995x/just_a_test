#include "button_controller.h"

Button_Controller::Button_Controller(System_State *system_state, uint8_t power_pin_1, uint8_t power_pin_2, uint8_t input_pin_1, uint8_t input_pin_2, uint8_t input_pin_3)
{
    m_system_state = system_state;
    m_power_pin_1 = power_pin_1;
    m_power_pin_2 = power_pin_2;
    m_input_pin_1 = input_pin_1;
    m_input_pin_2 = input_pin_2;
    m_input_pin_3 = input_pin_3;
    
    pinMode(m_power_pin_1, OUTPUT);
    digitalWrite(m_power_pin_1, LOW);

    pinMode(m_power_pin_2, OUTPUT);
    digitalWrite(m_power_pin_2, LOW);

    pinMode(m_input_pin_1, INPUT_PULLDOWN);
    pinMode(m_input_pin_2, INPUT_PULLDOWN);
    pinMode(m_input_pin_3, INPUT_PULLDOWN);
}

void Button_Controller::test_for_button_press()
{    
    int value = LOW;

    // First row of buttons
    digitalWrite(m_power_pin_1, HIGH);

    value = digitalRead(m_input_pin_1);
    if(value == HIGH)
    {
        m_system_state->set_pressed_button(BUTTON_BACK);
        digitalWrite(m_power_pin_1, LOW);
        return;
    }
    value = digitalRead(m_input_pin_2);
    if(value == HIGH)
    {
        m_system_state->set_pressed_button(BUTTON_SELECT);
        digitalWrite(m_power_pin_1, LOW);
        return;
    }
    value = digitalRead(m_input_pin_3);
    if(value == HIGH)
    {
        m_system_state->set_pressed_button(BUTTON_RIGHT);
        digitalWrite(m_power_pin_1, LOW);
        return;
    }

    

    // Second row of buttons
    digitalWrite(m_power_pin_2, HIGH);

    value = digitalRead(m_input_pin_1);
    if(value == HIGH)
    {
        m_system_state->set_pressed_button(BUTTON_LEFT);
        digitalWrite(m_power_pin_2, LOW);
        return;
    }
    value = digitalRead(m_input_pin_2);
    if(value == HIGH)
    {
        m_system_state->set_pressed_button(BUTTON_UP);
        digitalWrite(m_power_pin_2, LOW);
        return;
    }
    value = digitalRead(m_input_pin_3);
    if(value == HIGH)
    {
        m_system_state->set_pressed_button(BUTTON_DOWN);
        digitalWrite(m_power_pin_2, LOW);
        return;
    }

}
