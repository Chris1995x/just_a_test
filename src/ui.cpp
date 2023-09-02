#include "ui.h"

UI::UI(U8G2_ST7920_128X64_F_SW_SPI* display, System_State* system_state) {
  m_u8g2 = display;
  m_system_state = system_state;
  
  // Create all the screens
  m_screens = new std::map<Screen_Type, Screen*>();

  m_screen_manager = new Screen_Manager(m_screens);

  m_screens->insert(std::pair<Screen_Type, Screen*>(Screen_Type::START_SCREEN, new Start_Screen(m_u8g2, m_screen_manager)));
  m_screens->insert(std::pair<Screen_Type, Screen*>(Screen_Type::CREATE_PROGRAM_SCREEN, new Create_Program_Screen(m_u8g2, m_screen_manager)));
  m_screens->insert(std::pair<Screen_Type, Screen*>(Screen_Type::RUN_PROGRAM_SCREEN, new Running_Program_Screen(m_u8g2, m_screen_manager)));

  m_screen_manager->setCurrentScreen(Screen_Type::START_SCREEN);
}

UI::~UI(void)
{
  // Delete the screen manager
  delete m_screen_manager;
  m_screen_manager = nullptr;

  // Delete all screens
  for(auto it = m_screens->begin(); it != m_screens->end(); it++) {
    delete it->second;
    m_screens->erase(it);
  }

  // Delete the map
  delete m_screens;
  m_screens = nullptr;
}

void UI::initialize() {
  m_u8g2->begin();
}

void UI::drawUI() {
  
  m_u8g2->clearBuffer();

  m_screen_manager->drawCurrentScreen();

  m_u8g2->sendBuffer();
  
}