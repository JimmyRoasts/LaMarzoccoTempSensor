// This Firmware was developed from the Adafruit Thermistor example
// It uses an Arduino nano to read a thermistor on pin A2
// The thermistor is believed to be a 50k NTC thermistor
// Since the manufacturer is unknown the Beta Value is also unknown
// The model below seems to work okay, but any help is appreciated :)

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
//reference voltage

#define CLK 5 //Clock Line for LM1637
#define DIO 4 //IO Line for LM1637


TM1637Display display(CLK, DIO); 
 
int samples[NUMSAMPLES];

float sum = 0;                    // sum of samples taken
unsigned char sample_count = 0; // current sample number
float voltage = 0.0;            // calculated voltage
 
void setup(void) {
  display.setBrightness(0x07);
  Serial.begin(9600);
  analogReference(DEFAULT);
}
 
void loop(void) {
  uint8_t i;
  float average;

    // take a number of analog samples and add them up
    
    while (sample_count < NUMSAMPLES) {
        sum += (analogRead(THERMISTORPIN)*(VOLTAGEREF / 1023) * VOLTAGESCALE);
        sample_count++;
        delay(30);
    }
    
    // calculate the voltage
    // use 5.0 for a 5.0V ADC reference voltage
    // 4.61V is the calibrated reference voltage
    
    voltage = ((float)sum / (float)NUMSAMPLES);
    
    // send voltage for display on Serial Monitor
    // voltage multiplied by 12.1 when using voltage divider that
    // divides by 12.1

    Serial.print(voltage);
    Serial.println (" V");
    sample_count = 0;
    sum = 0;
  


  average = SERIESRESISTOR / (voltage / 0.92); //0.92 is a scaling factor that the thermistor seems to line up with.
  Serial.print("Thermistor resistance "); 
  Serial.println(average);
  
  float steinhart;
  steinhart = (SERIESRESISTOR / (VOLTAGEREF - voltage))/ THERMISTORNOMINAL;     // (R/Ro)
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


  display.showNumberDecEx(temp2*10,64,false);
  
}
