/**
 **************************************************
 *
 * @file        Wind-Direction-Library-SOLDERED.cpp
 * @brief       Example functions to overload in base class.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Goran Juric @ soldered.com
 ***************************************************/

#include "Wind-Direction-Library-SOLDERED.h"

/**
 * @brief                   Sensor specific native constructor.
 *
 * @param int _pin          Example parameter.
 */
WindDirectionSensor::WindDirectionSensor(int _pin, float _analogVoltage)
{
    pin = _pin;
    pinMode(pin, INPUT);

#ifndef ANALOG_VOLTAGE

#if defined(ARDUINO_ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_ATmega328)

    analogVoltage = 4.7; // Development board takes input voltage for reference for
                         // measuring analog voltage. 5 volts from USB input has slight
                         // voltage drop so we here compensate for that.

#elif defined(ARDUINO_ESP32_DEV) || defined(ARDUINO_ESP8266_GENERIC) || defined(ARDUINO_STM32F103)

    analogVoltage = 3.3;

#else

    analogVoltage = _analogVoltage;

#endif

#endif
    setADCWidth(10);
}

float WindDirectionSensor::getDegrees()
{
    float val = ((float)analogRead(pin) / (float)ADCWidth) * 360;
    if (val > 360)
    {
        return 0;
    }
    val += offset;
    while (val >= 360)
    {
        val -= 360;
    }
    while (val < 0)
    {
        val += 360;
    }
    return val;
}

/**
 * @brief                   Function which returns direction of the wind in degrees
 *
 * @return                  Wind direction in degrees
 *
 */
float WindDirectionSensor::windDirection()
{
    return getDegrees();
}

/**
 * @brief                   Function which sets ADC width
 *
 * @param   uint16_t value  ADC width to be set
 */
void WindDirectionSensor::setADCWidth(uint16_t _value)
{
    ADCWidth = ((1 << _value) - 1) * 3.3 / analogVoltage;
}

/**
 * @brief                   Function which gets ADC width
 *
 * @return                  ADC width
 */
uint16_t WindDirectionSensor::getADCWidth()
{
    return ADCWidth;
}

/**
 * @brief                   Function which returns wind direction in cardinal directions
 *
 * @return                  Wind direction in cardinal directions
 */
const char *WindDirectionSensor::cardinalDir()
{
    float val = windDirection();
    val += 11.25;
    if (val < 0)
    {
        val += 360;
    }
    return (const char *)cardinal_directions[(int)(val / 22.5) > 15 ? 0 : (int)(val / 22.5)];
}

/**
 * @brief                   Function which calibrates sensor to set North to 0 degrees
 *
 *
 */
void WindDirectionSensor::calibrate()
{
    float temp = getDegrees();
    offset = -temp;
}