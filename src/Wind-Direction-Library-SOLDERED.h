/**
 **************************************************
 *
 * @file        Wind-Direction-Library-SOLDERED.h
 * @brief       Header file for sensor specific code.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Goran Juric @ soldered.com
 ***************************************************/

#ifndef __WindDirection__
#define __WindDirection__

#include "Arduino.h"

const char cardinal_directions[][4] = {"N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE",
                                       "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"};

class WindDirectionSensor
{
  public:
    WindDirectionSensor(int _pin, float _analogVoltage = 5);
    float windDirection();
    void setADCWidth(uint16_t _value);
    uint16_t getADCWidth();
    const char *cardinalDir();
    void calibrate();

  protected:
  private:
    float getDegrees();
    int pin;
    uint16_t ADCWidth = 765;
    float offset = 0;
    float analogVoltage = 5;
};

#endif