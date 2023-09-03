#include "temperatur_controller.h"

Temperatur_Controller::Temperatur_Controller(System_State *system_state, uint8_t cs_pin /*CS*/, uint8_t clock_pin /*CLK*/, uint8_t data_pin /*D0*/, uint8_t relay_pin)
{
    m_system_state = system_state;
    m_max31855 = new Adafruit_MAX31855(cs_pin, clock_pin, data_pin);
    m_relay_pin = relay_pin;
}

void Temperatur_Controller::initialize(void)
{
    pinMode(m_relay_pin, OUTPUT);
    digitalWrite(m_relay_pin, LOW);

    if(!m_max31855->begin()) {
        m_system_state->set_oven_state(OVEN_ERROR);
    }
}

void Temperatur_Controller::updateState(uint16_t passed_time_in_ms)
{
    int16_t target = m_system_state->get_current_target_temperatur();

    //TODO: Read the current temperature from the sensor.
    int16_t sensor_tmp = (int16_t)m_max31855->readCelsius();
    if(sensor_tmp < MAX_TEMPERATURE) {
        m_system_state->set_current_temperature(sensor_tmp);
    } else {
        m_system_state->set_oven_state(OVEN_ERROR);
        digitalWrite(m_relay_pin, LOW);
    }

    switch (m_system_state->get_oven_state())
    {
        case OVEN_ON:
            updateRelayState(sensor_tmp, target);
            m_system_state->update_current_time((uint32_t)passed_time_in_ms);
            break;
        case OVEN_HOLD:            
            updateRelayState(sensor_tmp, target);
            break;
        case OVEN_OFF:
            digitalWrite(m_relay_pin, LOW);
            break;
        default:
            digitalWrite(m_relay_pin, LOW);
            break;
    }
}

void Temperatur_Controller::updateRelayState(int16_t current_temperature, int16_t target_temperature)
{
    if(current_temperature < target_temperature)
    {
        digitalWrite(m_relay_pin, HIGH);
    }
    else
    {
        digitalWrite(m_relay_pin, LOW);
    }
}
