// Based on - Thermistor Example #3 from the Adafruit Learning System guide on Thermistors 
// https://learn.adafruit.com/thermistor/overview by Limor Fried, Adafruit Industries
// MIT License - please keep attribution and consider buying parts from Adafruit
//
// Linea Mini Temperature Display Circuit
// Author - JDavison 04/12/2019
// 
// This circuit is designed to read the Thermistor input from the Linea mini (home)
// Thermistor values are derived from data supplied by La Marzocco AU
// 
// The thermistor is set up like a voltage divider as follows
// 
//  +5v Supply ---> 6.19k resistor ---> NTC ~50k Thermistor ---> 100k resistor ---> decoupling capactior | ----> GND
//                                                                                              |
//                                                                                              |
//                                                                                       Main Board Read voltage
//
//
// The arduino just passes the signal back to the Linea mini, but reads the voltage as well, effectively working as a volt meter
// The voltage read is coverted into temperature using the Steinhart-Hart equation
// This particular arduino only outputs 4.5v when powered from USB, so pay close attention to how it is reading voltage. Normal values should be +5v
// 2.02v across the thermistor should correspond to roughly 93 degrees Celcius 
// Design also incorporates LM4040 reference diode for more accurate measurement



#include <Arduino.h>
#include <TM1637Display.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// which analog pin to connect
#define THERMISTORPIN A2         
// resistance at 25 degrees C
#define THERMISTORNOMINAL 49120 //from LM Data supplied      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   //using 25 degrees
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5 //used for quicker updating
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3977 //calculated based on LM data
// the value of the 'other' resistor
#define SERIESRESISTOR 6190 //measured on board

#define VOLTAGEREF 4.103 //measured between LM4040 and GND

#define LMREF  5.07 //measured from LMBoard --- GND Board

#define ReportDelay 500 //500 milliseconds between reports


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  
 
int samples[NUMSAMPLES];

float sum = 0;                    // sum of samples taken
unsigned char sample_count = 0; // current sample number
float voltage = 0.0;            // calculated voltage
float THERMISTORRES = 0.00; // Thermistor calculated resistance

unsigned int ADCValue;
double Voltage;
double Vcc;

unsigned long previousMillis=0;

float steinhart; //variable to hold steinhart equation result

 
void setup(void) {

  analogReference(EXTERNAL);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();

}

void loop(void) {
  uint8_t i;
  float average;

  unsigned currentMillis= millis(); //Get the current time
    
    // take a number of analog samples and add them up
    while (sample_count < NUMSAMPLES) {
      
        sum += ((analogRead(THERMISTORPIN) * VOLTAGEREF)/1024);

        sample_count++;
    }

    voltage = ((float)sum / (float)NUMSAMPLES);

    // send voltage for display on Serial Monitor

    Serial.print(voltage);
    Serial.println (" V");
    
    sample_count = 0;
    sum = 0;
  
  THERMISTORRES = SERIESRESISTOR * (1/((LMREF / voltage) -1));

  average = SERIESRESISTOR / voltage;
  Serial.print("Thermistor resistance "); 
  Serial.println(THERMISTORRES);
  
  steinhart = THERMISTORRES / THERMISTORNOMINAL;
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert to C
  steinhart /= 1.0;
  
  Serial.print("Temperature "); 
  Serial.print(steinhart);
  Serial.println(" *C");

  int temp = steinhart*100;
  float temp2 = temp/10;

  if ((currentMillis - previousMillis)>= ReportDelay){
    lcdReport(); //refresh the lcd
    previousMillis = millis(); //reset the timer
  }

  voltage = 0; //reset
  THERMISTORRES = 0; //reset
  average = 0;// reset
  temp = 0;//reset
  temp2 = 0; //reset 
}

void lcdReport(){
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Voltage: ");
   lcd.print(voltage,2);
   lcd.setCursor(0,1);
   lcd.print("Temp: ");
   lcd.print(steinhart,1);

}
