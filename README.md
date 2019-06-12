# LaMarzoccoTempSensor
Temperature Sensor for the LMHome Mini

This project uses the Thermistor in the La Marzocco Home Mini (Linea Mini) to read the temperature of the brew boiler.
The code is uploaded to and Arduino Nano or similar and read on the analogRead Pin. The temperature is then read out on a 4 digit display however this part of the project isn't stricly neccessary.

The steinhart sheet is Excel sheet I developed to have a look at how the changing resistance changes the reading of the temperature. Because I don't know the manufacturer specs of the Thermistor this has been an exercise in reverse engineering. The model may be a little off.

Current I think it's a 50K NTC thermistor with a beta value of 4400. I based this on some resitance readings I took and the observed sensor behaviour. 

To install;

1. Upload ino file to arduino nano, if you need the TM1367 library, I've included that too.
2. The thermistor header from the main LM board will have 2 pins. 1 is GND and the other is Signal. The signal pin needs to be read by pin A2 on the arduino. You will need to make up a custom header for this.
