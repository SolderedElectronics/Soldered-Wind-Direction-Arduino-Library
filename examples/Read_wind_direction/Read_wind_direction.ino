/**
 **************************************************
 *
 * @file        Read_wind_direction.ino
 * @brief       Example for reading wind direction
 *
 * @link        product: https://www.solde.red/333197
 *
 * @authors     Goran Juric @ soldered.com
 ***************************************************/

#include "Wind-Direction-Library-SOLDERED.h"

#define WIND_DIR_PIN A0          // This sensor needs to be connected on analog pin

WindDirectionSensor windDir(WIND_DIR_PIN); // Create object and specify pin on
                                           // which is sensor connected.
                                           
void setup()
{
    Serial.begin(115200); // Begin serial communication with PC
    
    Serial.println("Set wind direction sensor to point North.");
    delay(1500);
    windDir.calibrateDirection(); // Calibrate sensor to 0 degrees. This should be
                                  // called only on power up (or anywhere else in code, 
                                  // but it is not necessary if it is called here), you 
                                  // should set sensor to point directly to North at power 
                                  // up, when this function is called in order to get wind
                                  // directions correct.
    Serial.println("Direction calibrated.");
    delay(1000);
    Serial.println("Turn sensor around once...");
    delay(1000);
    Serial.println("Calibrating.");
    windDir.calibrateADC();       // This function will calibrate sensor by taking measures
                                  // in all possible positions of sensor and will scale measures
                                  // in that range.
    Serial.println("ADC calibrated. Sensor is now fully calibrated and ready to measure!");

}

void loop()
{
    Serial.print("Wind direction azimuth: "); // Print message
    Serial.println(windDir.windDirection());  // Get and print wind direction azimuth
                                              // If your sensor has some movement where is 
                                              // reading constantly zero, or if some angles are missing
                                              // from 0 to 360 degrees, please set ANALOG_INPUT_VOLTAGE
                                              // macro definition as stated in line #16

    Serial.print("Wind direction: ");         // Print message
    Serial.println(windDir.cardinalDir());    // Get cardinal direction of wind
    Serial.println(analogRead(A0));
    delay(1000);
}
