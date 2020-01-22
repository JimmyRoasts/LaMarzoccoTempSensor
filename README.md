# LaMarzoccoTempSensor
Temperature Sensor for the LMHome Mini

This project uses the Thermistor in the La Marzocco Home Mini (Linea Mini) to read the temperature of the brew boiler.
The code is uploaded to and Arduino Nano or similar and read on the analogRead Pin. The temperature now gets displayed on a 16x2 LCD display commmunicating over I2C

The steinhart sheet is Excel sheet I developed to have a look at how the changing resistance changes the reading of the temperature. This has been updated with data supplied by La Marzocco Australia. The derivation of the B value for the thermistor can be found in the updated spreadsheet.

Values for the Thermistor are as follows:

Nominal Resistance - 49120 Ohms
Nominal Temp = 25 deg C
Beta = 3977

The arduino needs the addition of a LM4040 reference diode for accurate measurement. The temperature range is measured generally between 2.1v to 1.78v. That means high accuracy of measurement is essential.

I've created a custom control board and circuit which can be found here. I suggest ordering from JLPCB. 

https://easyeda.com/williamstownroasters/lm-temperature-sensor **Tested and Working** Dec, 2019

To install;

1. Upload ino file to arduino nano, if you need the TM1367 library, I've included that too.
2. The thermistor header from the main LM board will have 2 pins. 1 is GND and the other is Signal. The signal pin needs to be read by pin A2 on the arduino. You will need to make up a custom header for this.

I've got a few documents that describe how the board is setup on the home mini for reference. Makre sure your jumper wires are installed correctly.
