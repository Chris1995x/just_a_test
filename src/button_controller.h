#ifndef BUTTON_CONTROLLER_H
#define BUTTON_CONTROLLER_H

#include "system_state.h"

class Button_Controller {
    public:
        Button_Controller(System_State* system_state);
    
    public:
        void test_for_button_press();

    private:
        System_State* m_system_state;
};

#endif