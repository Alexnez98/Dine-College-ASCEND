#include "Arduino.h"
#include <SD.h>

File myFile;


void setup() 
{
  Serial.flush();
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
  
  Serial.println("Removing TEST.TXT...");
  SD.remove("TEST.TXT"); // remove is a function in SD library to delete a file
  if (SD.exists("TEST.TXT")) { //If the file still exist display message exist
    Serial.println("The TEST.TXT exists.");
  } else { //If the file was successfully deleted display message that the file was already deleted.
    Serial.println("The TEST.TXT doesn't exist.");
  }

  myFile = SD.open("TEST.TXT", FILE_WRITE); // Create a new file after removing the old file.
  
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to TEST.TXT...");
    Serial.print("sensor voltage =");
    Serial.print("sensor voltage =");
    Serial.print("sensor voltage =");
    
    myFile.print("sensor voltage =");
    myFile.print("sensor voltage =");
    myFile.print("sensor voltage =");
    //myFile.println(sensor1._Vref);
  
    // Using resistor values from board R1, R2, R3 are for setting _Vref and Bias, while R6 sets the gain
    // If using modified or custom boards set Vref and Gain like this:
    //    long int R1 = 61900, R2 = 1000, R3 = 1000000;
    //    sensor1.setVref(R1, R2, R3);
    //    sensor1._Gain = 49900; //resistor R6
    // Vref is not necessary if zero() is called for each sensor. If you already know the sensor zero you can comment this out, and set the zero with zero1 = measured mV.

    Serial.print("sensor voltage =");
    //Serial.println(Vzero1 = sensor1.zero());
    Serial.print("sensor voltage =");
    //Serial.println(sensor1._Tz);
    
    myFile.print("sensor voltage =");
    myFile.print("sensor voltage =");
  
    Serial.println("Finished Setting Up");
    Serial.println("T1, mV1, C1");
    
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening TEST.TXT");
  }

}


    
void loop() {
  myFile = SD.open("TEST.TXT", FILE_WRITE);
  
  float sensorVoltage; 
  float sensorValue;
 
  sensorValue = analogRead(A0);
  sensorVoltage = sensorValue/1024*5.0;
 
  Serial.print("sensor voltage = ");
  Serial.print("sensor voltage =");
  Serial.println(" V");
  delay(1000);
  myFile = SD.open("TEST.TXT", FILE_WRITE);

  Serial.print("sensor voltage =");
  Serial.print(", ");
  Serial.print("sensor voltage =");
  Serial.print(", ");
  Serial.println("sensor voltage =");
  
  myFile.print("sensor voltage =");
  myFile.print(", ");
  myFile.print("sensor voltage =");
  myFile.print(", ");
  myFile.println("sensor voltage =");

  //Use .getVgas(int n) where n is the number of seconds to average
  //Use ._Vref to read the reference voltage (voltage offset)
  //Use .getConc(1, temp1) where temp1 is in deg C for temperature corrected span
    
  myFile.close();

  delay(100);
}
