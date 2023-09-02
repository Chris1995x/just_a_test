#ifndef START_SCREEN_H
#define START_SCREEN_H

#include <list>
#include <U8g2lib.h>

#include "system_state.h"
#include "ui_screen_manager.h"
#include "ui_screen.h"
#include "ui_temperatur_box.h"
#include "ui_state_box.h"

#define SELECTABLE_BOXES 3



class Start_Screen : public Screen {
    public:
        Start_Screen(U8G2_ST7920_128X64_F_SW_SPI* display, System_State* system_state, Screen_Manager* screen_manager);
        ~Start_Screen();

    public:
        void drawScreenToBuffer();
        void up();
        void down();
        void left();
        void right();
        void select();
        void back();
    
    private:
        void drawToggleButton();
        void drawProgramButton();

    private:        
        enum Available_Boxes {
            TARGET_TEMPERATUR_BOX,
            TOGGLE_BUTTON,
            PROGRAM_BUTTON
        };
        U8G2_ST7920_128X64_F_SW_SPI* m_u8g2;
        System_State* m_system_state;
        Screen_Manager* m_screen_manager;
        Temperatur_Box* m_target_temperatur_box;
        Temperatur_Box* m_current_temperatur_box;
        State_Box* m_state_box;
        Available_Boxes m_highlighted_box;
};

#endif