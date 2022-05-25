/**
 **************************************************
 *
 * @file        Read_wind_direction.ino
 * @brief       Example for reading wind direction
 *
 *
 *
 * @authors     Goran Juric @ soldered.com
 ***************************************************/

#include "Wind-Direction-Library-SOLDERED.h"

#define WIND_DIR_PIN A0          // This sensor needs to be connected on analog pin

//#define ANALOG_INPUT_VOLTAGE 5 // If you are not using development board made by Soldered
                                 // you should uncomment this line and specify maximum 
                                 // voltage for analog input pins of your development board.
                                 // If board does't use 3.3V on input of analog pins, then
                                 // you need to measure input voltage on 5V line of
                                 // development board and set it int this macro definition

WindDirectionSensor windDir(WIND_DIR_PIN); // Create object and specify pin on
                                           // which is sensor connected.
                                           
//WindDirectionSensor windDir(WIND_DIR_PIN, ANALOG_INPUT_VOLTAGE);  // If you are not using development board made by Soldered
                                                                    // this line should be uncommented to specify voltage of analog input


void setup()
{
    Serial.begin(115200); // Begin serial communication with PC
    
    windDir.setADCWidth(10);  // If your development board has wider
                              // ADC than 10 bits, you should set it here in
                              // to sensor work right

    windDir.calibrate();      // Calibrate sensor to 0 degrees. This should be
                              // called only on power up, you should set sensor
                              // to point directly to North at power up, when this
                              // function is called in order to get wind directions
                              // correct.

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
    delay(1000);
}
