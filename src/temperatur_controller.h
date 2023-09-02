#ifndef OVEN_CONTROLLER_H
#define OVEN_CONTROLLER_H

#include <U8g2lib.h>

#include "system_state.h"

class Temperatur_Controller {
  public:
    Temperatur_Controller(System_State* system_state);

  public:
    void updateState(uint16_t passed_time_in_ms);

  private:

  private:
   System_State* m_system_state;
};

#endif