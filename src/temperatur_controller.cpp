#include "temperatur_controller.h"

Temperatur_Controller::Temperatur_Controller(System_State *system_state)
{
    m_system_state = system_state;
}

void Temperatur_Controller::updateState(uint16_t passed_time_in_ms)
{
    //TOOD: Read the target temperature from the system state.
    int16_t target = m_system_state->get_current_target_temperatur();

    //TODO: Read the current temperature from the sensor.
    // int16_t sensor_tmp = ...;
    // m_system_state->set_current_temperature(sensor_tmp);

    // If the oven is ON and the temperature controller is not overridden 
    // then try to reach the target temperatur.
    if(m_system_state->get_oven_state() && !m_system_state->get_override_temp_controller())
    {
        //TODO: Compasre the current temperature with the target temperature.
        /*
        if(target < sensor_tmp)
        {
            turn on the relay for the heater
        }
        */
    }

    m_system_state->update_current_time((uint32_t)passed_time_in_ms);
}
