#include "temperatur_controller.h"

Temperatur_Controller::Temperatur_Controller(System_State *system_state)
{
    m_system_state = system_state;
}

void Temperatur_Controller::updateState(uint16_t passed_time_in_ms)
{
    int16_t target = m_system_state->get_current_target_temperatur();

    //TODO: Read the current temperature from the sensor.
    int16_t sensor_tmp = 0;
    if(sensor_tmp < MAX_TEMPERATURE) {
        m_system_state->set_current_temperature(sensor_tmp);
    } else {
        m_system_state->set_oven_state(OVEN_ERROR);
    }

    switch (m_system_state->get_oven_state())
    {
        case OVEN_ON:
            break;
        case OVEN_HOLD:
            break;
        case OVEN_OFF:
            break;
        default:
            break;
    }
    /*if(m_system_state->get_oven_state() && !m_system_state->get_override_temp_controller())
    {
        //TODO: Compasre the current temperature with the target temperature.
        /*
        if(target < sensor_tmp)
        {
            turn on the relay for the heater
        }
        */
    //}

    m_system_state->update_current_time((uint32_t)passed_time_in_ms);
}
