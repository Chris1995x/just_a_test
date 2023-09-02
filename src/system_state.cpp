#include <list>
#include <stdint.h>
#include <memory>
#include <chrono>

#include "system_state.h"

System_State::System_State()
{
    m_oven_state = false;
    m_override_temp_controller = false;

    m_last_pressed_button = BUTTON_NONE;
    m_current_pressed_button = BUTTON_NONE;

    m_current_temperature = 0;

    m_current_time = new time_s();
    m_current_time->hour = 0;
    m_current_time->minute = 0;
    m_current_time->millisecond = 0;

    m_program = new std::list<program_point*>();
}

System_State::~System_State()
{
    clear_program();

    //Remove the list.
    delete m_program;
    m_program = nullptr;

    delete m_current_time;
    m_current_time = nullptr;
}

/****************************************************\
 * Methods to start, stopp and lock the oven 
\****************************************************/
bool System_State::get_oven_state(void) const
{
    return m_oven_state;
}

bool System_State::get_override_temp_controller(void) const
{
    return m_override_temp_controller;
}

void System_State::set_oven_state(bool oven_state)
{
    m_oven_state = oven_state;
}

void System_State::set_override_temp_controller(bool override_temp_controller)
{
    m_override_temp_controller = override_temp_controller;
}

/****************************************************\
 * Methods to handle the user input
\****************************************************/
void System_State::set_pressed_button(Available_Buttons pressed_button)
{
    if (m_last_pressed_button != pressed_button && m_current_pressed_button == BUTTON_NONE)
    {
        m_current_pressed_button = pressed_button;
    }
}

Available_Buttons System_State::get_pressed_button(void)
{
    Available_Buttons temp = m_current_pressed_button;
    m_last_pressed_button = m_current_pressed_button;
    m_current_pressed_button = BUTTON_NONE;
    return temp;
}

/****************************************************\
 * Methods to handle the program 
\****************************************************/
void System_State::add_program_point(uint16_t target_temperature, time_s* time_interval, Program_Point_Type type)
{
    program_point* point = new program_point();
    point->step = m_program->size() + 1/*list starts at 0*/;
    point->target_temperature = target_temperature;
    point->time_interval = time_interval;
    point->type = type;

    // Add new point to the back of the queue
    m_program->push_back(point);
}

Program_Point_Type System_State::get_current_program_type(void) const
{
    return m_program->front()->type;
}

uint8_t System_State::get_current_program_step(void) const
{
    return m_program->front()->step;
}

void System_State::update_current_time(uint32_t passed_time_in_ms)
{
    // Update the current time
    m_current_time->millisecond += passed_time_in_ms;

    if(m_current_time->millisecond > MILLISECONDS_IN_MINUTE - 1)
    {
        m_current_time->millisecond -= MILLISECONDS_IN_MINUTE;
        m_current_time->minute++;
    }

    if(m_current_time->minute > MINUTES_IN_HOUR - 1)
    {
        m_current_time->minute = 0;
        m_current_time->hour++;
    }


    // Load the next program point
    if(m_current_time->hour >= m_current_target_time_interval->hour &&
       m_current_time->minute >= m_current_target_time_interval->minute)
    {
        // Remove the first element in the list.
        program_point* point = m_program->front();

        // Remove the time structure from heap
        delete point->time_interval;
        point->time_interval = nullptr;

        // Remove the program point entry from heap
        delete point;
        point = nullptr;

        // Load the new target values
        m_program->pop_front(); 
        m_current_target_temperature = m_program->front()->target_temperature;
        m_current_target_time_interval = m_program->front()->time_interval;
        
        // Reset the time
        m_current_time->hour = 0;
        m_current_time->minute = 0;
        m_current_time->millisecond = 0;
    }
}

void System_State::clear_program()
{
    // Remove all the list entries.
    while (!m_program->empty()) {
        program_point* point = m_program->front();

        // Remove the time structure from heap
        delete point->time_interval;
        point->time_interval = nullptr;

        // Remove the program point entry from heap
        delete point;
        point = nullptr;

        m_program->pop_front();
    }
}

/****************************************************\
 * Methods to handle the target parameters directly 
\****************************************************/

void System_State::set_current_temperature(int16_t current_temperature)
{
    m_current_temperature = current_temperature;
}

int16_t System_State::get_current_temperature(void) const
{
    return m_current_temperature;
}

void System_State::set_current_target_temperature(int16_t new_target_temperature)
{
    m_current_target_temperature = new_target_temperature;   
}

int16_t System_State::get_current_target_temperatur(void) const
{
    return m_current_target_temperature;
}

time_s* System_State::get_current_time(void) const
{
    return m_current_time;
}


