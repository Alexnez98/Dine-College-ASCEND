/*
  ULP - Library for reading SPEC Sensors ULP.
  Created by David E. Peaslee, OCT 27, 2017.
  Released into the SPEC Sensors domain.
*/

/* The library is built to use several SPEC ULP sensors. 
 *  An Arduino Uno can handle 3 sensors, since 2 analog pins are required for each sensor.
 *  
 *  Functions include: 
 *    getTemp(seconds, C/F): returns temperature, 
 *    setTSpan(seconds, "HIGH"/"LOW"): for calibrating temperature, 
 *    setVref(R1,R2,R3) for custom sensors, 
 *    getVgas(seconds): for getting voltage of sensor, 
 *    getConc(seconds, temperature in degC): for getting temperature corrected concentration, 
 *    setXSpan(): for setting the calibration factor with known concentration of gas. 
 *  Variables include 
 *     _Vcc: the voltage ref of the ADC, 
 *    _Vsup: the voltage to the ULP, 
 *    _Gain the value of resistor R6. 
 *    
 *  For more details see ULP.cpp in the libraries folder and the data sheet 
 *  at http://www.spec-sensors.com/wp-content/uploads/2016/06/Analog-SDK-Users-Manual-v18.pdf
*/  

/* As an example, the ULP is connected this way: 
 *    Vgas (pin1) to A0, 
 *    Vtemp (Pin3) to A3, 
 *    Gnd (Pin6) to Gnd, 
 *    V+ (Pin7 or Pin8) to 3.3V of Arduino (must not be above 3.3V!!!).
*/

#include "Arduino.h"
#include "ULP.h"
#include <SD.h>

File myFile;

// These constants won't change.  They're used to give names to the pins used and to the sensitivity factors of the sensors:

const int C1 = A0;
const int T1 = A3;
//const int C2 = A1;
//const int T2 = A4;

const float Sf1 = 4.05; //nA/ppm
//const float Sf2 = -56.45;

float temp1;
float TZero;
float Vzero1;
//float temp2;
//float zero2;

NO2 sensor1(C1, T1, Sf1);	//Sensor Types are EtoH, H2S, CO, IAQ, SO2, NO2, RESP, O3, and SPEC (custom)
//SO2 sensor1(C1, T1, Sf1); // SO2
//O3 sensor2(C2, T2, Sf2);	//Example O3
//H2S sensor3(C3, T3, Sf3);	//Example H2S

//  Include these if using different boards with different voltages
//float ULP::_Vcc = 5.0;  //analogRead Reference Voltage
//float ULP::_Vsup =3.3;  //voltage supplied to V+ of ULP, ideally 3.3 Volts 


void setup() {

  // Serial.flush();
  Serial.begin(9600);    // initialize serial communications at 9600 bps:

  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
   pinMode(10, OUTPUT);
 
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  
  Serial.println("initialization done.");
 
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");

    myFile.print("Vsup for all sensors = ");
    myFile.println(ULP::_Vsup);
    myFile.print("Vcc for all sensors = ");
    myFile.println(ULP::_Vcc);
    myFile.print("Vref for sensor 1 = ");
    myFile.println(sensor1._Vref);
  
    // Using resistor values from board R1, R2, R3 are for setting _Vref and Bias, while R6 sets the gain
    // If using modified or custom boards set Vref and Gain like this:
    //    long int R1 = 61900, R2 = 1000, R3 = 1000000;
    //    sensor1.setVref(R1, R2, R3);
    //    sensor1._Gain = 49900; //resistor R6
    // Vref is not necessary if zero() is called for each sensor. If you already know the sensor zero you can comment this out, and set the zero with zero1 = measured mV.
  
    myFile.print("Vzero = ");
    myFile.println(Vzero1 = sensor1.zero());   //.zero() sets and returns the baseline voltage at current temperature with only clean air present
    myFile.print("Tzero = ");
    myFile.println(sensor1._Tz);
  
    //sensor1.setXSpan();                                //Must have previously zeroed in clean air, returns new span factor.

    //When calibrating the temperature use "LOW"/"HIGH" for the temperature range ie .setTSpan(40.2, "HIGH") where T is the current high temperature
    sensor1.setTSpan((71 - 32.0) * 5.0 / 9.0, "LOW");

    myFile.println("Finished Setting Up");
    myFile.println("T1, mV1, C1");
    
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

}

void loop() {
  myFile = SD.open("test.txt", FILE_WRITE);
  
  temp1 = sensor1.getTemp(1, "F");  // Use .getTemp(n, "F") to get temp in Fahrenheit, with n as int number of seconds for averaging and "F" or "C" for temp units
    
  myFile.print(temp1);
  myFile.print(", ");

  //Use .getVgas(int n) where n is the number of seconds to average
  //Use ._Vref to read the reference voltage (voltage offset)
  myFile.print(sensor1.getVgas(1));

  //Use .getConc(1, temp1) where temp1 is in deg C for temperature corrected span
  myFile.print(", ");
  myFile.println(sensor1.getConc(1,temp1));
  myFile.close();

  delay(100);
}
