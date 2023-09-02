#ifndef BUTTON_CONTROLLER_H
#define BUTTON_CONTROLLER_H

#include <Arduino.h>
#include "system_state.h"

class Button_Controller {
    public:
        Button_Controller(System_State* system_state, uint8_t power_pin_1, uint8_t power_pin_2, uint8_t input_pin_1, uint8_t input_pin_2, uint8_t input_pin_3);
    
    public:
        void test_for_button_press();

    private:
        System_State* m_system_state;
        uint8_t m_power_pin_1;
        uint8_t m_power_pin_2;
        uint8_t m_input_pin_1;
        uint8_t m_input_pin_2;
        uint8_t m_input_pin_3;
};

#endif