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
    WindDirectionSensor(int _pin);
    float windDirection();
    const char *cardinalDir();
    void calibrateDirection();
    void calibrateADC();

  protected:
  private:
    float getDegrees();
    int pin;
    uint16_t ADCWidth = 765;
    float offset = 0;
};

#endif