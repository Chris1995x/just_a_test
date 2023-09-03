#ifndef OVEN_CONTROLLER_H
#define OVEN_CONTROLLER_H

#include <U8g2lib.h>
#include "Arduino.h"
#include "Adafruit_MAX31855.h"

#include "system_state.h"

class Temperatur_Controller {
  public:
    Temperatur_Controller(System_State* system_state, uint8_t cs_pin /*CS*/, uint8_t clock_pin /*CLK*/, uint8_t data_pin /*D0*/, uint8_t relay_pin);

  public:
    void initialize(void);
    void updateState(uint16_t passed_time_in_ms);
  
  private:
    void updateRelayState(int16_t current_temperature, int16_t target_temperature);

  private:
    System_State* m_system_state;
    Adafruit_MAX31855* m_max31855;
    uint8_t m_relay_pin;
};

#endif