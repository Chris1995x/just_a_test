#include "ui_screen_manager.h"

Screen_Manager::Screen_Manager(std::map<Screen_Type, Screen*>* available_screens)
{
    m_screens = available_screens;
}

void Screen_Manager::drawCurrentScreen()
{
    if(m_current_screen != nullptr) {
        m_current_screen->drawScreenToBuffer();
    }
}

Screen* Screen_Manager::getCurrentScreen()
{
    return m_current_screen;
}

void Screen_Manager::setCurrentScreen(Screen_Type screen_type)
{
    if(m_screens->find(screen_type) != m_screens->end()) {
        m_current_screen = m_screens->at(screen_type);
    }
}
