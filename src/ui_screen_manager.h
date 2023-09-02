#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include <map>

#include "ui_screen.h"

class Screen_Manager {
    public :
        Screen_Manager(std::map<Screen_Type, Screen*>* available_screens);

    public:
        void drawCurrentScreen();
        Screen* getCurrentScreen();
        void setCurrentScreen(Screen_Type screen_type);

    private:
        Screen* m_current_screen;
        std::map<Screen_Type, Screen*>* m_screens;
};

#endif