#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include <list>
#include <stdint.h>
#include <memory>

#define MAX_TEMPERATURE 1300

#define MINUTES_IN_HOUR 60
#define MILLISECONDS_IN_MINUTE 60000 // A minute has 60 sec. * 1000 ms. = 60000 ms.

enum Available_Buttons {
    BUTTON_NONE,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_SELECT,
    BUTTON_BACK
};

enum Program_Point_Type {
    HOLD_TEMPERATUR,
    RAMP_TEMPERATUR,
    RAMP_TEMPERATUR_POINT
};

struct time_s {
    uint8_t hour;
    uint8_t minute;
    uint16_t millisecond;
};

struct program_point {
    uint8_t step;
    int16_t target_temperature;
    time_s* time_interval;
    Program_Point_Type type;
};

class System_State
{
public:
    System_State();
    ~System_State();

    bool get_oven_state(void) const;
    bool get_override_temp_controller(void) const;
    void set_oven_state(bool oven_state);
    void set_override_temp_controller(bool override_temp_controller);

    void set_pressed_button(Available_Buttons button);
    Available_Buttons get_pressed_button(void);

    void add_program_point(uint16_t target_temperature, time_s* time_interval, Program_Point_Type type);
    Program_Point_Type get_current_program_type(void) const;
    uint8_t get_current_program_step(void) const;
    void update_current_time(uint32_t passed_time_in_ms);
    void clear_program();

    void set_current_temperature(int16_t current_temperature);
    int16_t get_current_temperature(void) const;
    void set_current_target_temperature(int16_t new_target_temperature);
    int16_t get_current_target_temperatur(void) const;
    time_s* get_current_time(void) const;

    
    

private:
    bool m_oven_state;
    bool m_override_temp_controller;
    Available_Buttons m_current_pressed_button;
    Available_Buttons m_last_pressed_button;
    int16_t m_current_temperature;
    int16_t m_current_target_temperature;
    time_s* m_current_time;
    time_s* m_current_target_time_interval;
    std::list<program_point*>* m_program;
};

#endif