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
WindDirectionSensor::WindDirectionSensor(int _pin)
{
    pin = _pin;
    pinMode(pin, INPUT);
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
void WindDirectionSensor::calibrateDirection()
{
    float temp = getDegrees();
    offset = -temp;
}

/**
 * @brief                   Function which calibrates sensor to make it measure correct angle
 *
 *
 */
void WindDirectionSensor::calibrateADC()
{
    bool calibDone = 0;
    uint16_t now = 0, prev = 0, max = 0;
    uint8_t cnt = 0;
    while (!calibDone)
    {
        now = analogRead(pin);
        if (now > max)
        {
            max = now;
        }
        if (now < max)
        {
            cnt++;
        }
        else
        {
            cnt = 0;
        }
        if (cnt > 250)
        {
            calibDone = 1;
        }
        prev = now;
        delay(10);
    }
    ADCWidth = max;
}