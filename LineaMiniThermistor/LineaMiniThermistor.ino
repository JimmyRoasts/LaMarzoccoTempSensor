// This Firmware was developed from the Adafruit Thermistor example
// 

#include <Arduino.h>
#include <TM1637Display.h>
 
// which analog pin to connect
#define THERMISTORPIN A2         
// resistance at 25 degrees C
#define THERMISTORNOMINAL 50000      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 100
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 4400
// the value of the 'other' resistor
#define SERIESRESISTOR 6960

#define VOLTAGESCALE 12.1
//scaling value to convert voltage

#define VOLTAGEREF 4.585
