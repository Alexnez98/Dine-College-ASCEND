/*
  This test code is write for Arduino AVR Series(UNO, Leonardo, Mega)
  If you want to use with LinkIt ONE, please connect the module to D0/1 and modify:
  // #include <SoftwareSerial.h>
  // SoftwareSerial s_serial(2, 3);      // TX, RX
  #define sensor Serial1
*/


#include <SoftwareSerial.h>
SoftwareSerial s_serial(2, 3);      // TX, RX

//#include "Arduino.h"
#include <SD.h>

File myFile;

#define sensor s_serial

const unsigned char cmd_get_sensor[] =
{
    0xff, 0x01, 0x86, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x79
};

unsigned char dataRevice[9];
int CO2PPM;

void setup()
{
    sensor.begin(9600);
    //Serial.flush();
    Serial.begin(9600);
    
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
      Serial.println("The TEST.TXT was deleted.");
    }


    myFile = SD.open("TEST.TXT", FILE_WRITE); // Create a new file after removing the old file.
    // if the file opened okay, write to it:

    if (myFile) {

      Serial.print("Writing to TEST.TXT...");
      Serial.print("Co2_ppm");
      myFile.print("Co2_ppm");

      Serial.print(", ");
      myFile.print(", ");

      Serial.println("Temp");
      myFile.println("Temp");    

      // close the file:
      myFile.close();

    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening TEST.TXT");
    }
}

void loop()
{
    if(dataRecieve())
    {
        Serial.println(CO2PPM);
        // Serial.print(", ");
        // Serial.print(temp);

        myFile.println(CO2PPM);
        // myFile.print(", ");
        // myFile.print(temp);

    }
    delay(1000);
}




bool dataRecieve(void)
{
    byte data[9];
    int i = 0;

    //transmit command data
    for(i=0; i<sizeof(cmd_get_sensor); i++)
    {
        sensor.write(cmd_get_sensor[i]);
    }
    Serial.flush();
    
    //begin reveiceing data
    if(sensor.available())
    {
        while(sensor.available())
        {
            for(int i=0;i<9; i++)
            {
                data[i] = sensor.read();
            }
        }
    }

    for(int j=0; j<9; j++)
    {
       Serial.print(data[j],HEX);
        Serial.print(", ");
    }
    //Serial.print("");

    // First calculate then validate the check sum as there is no point in proceeding if the packet is corrupted. (code inspired by datasheet algorithm)
    byte checksum = 0 ;
    for(int j=1; j<8; j++)
    {
      checksum += data[j];
    }
    checksum=0xff-checksum; 
    checksum+=1;
       
    if  (checksum != data[8])
    {
      Serial.println("Error checksum");
      return false;
    }

    // Then check the start byte to make sure response is what we were expecting
    if ( data[0] != 0xFF )
    {
        Serial.println("Error start byte");
        return false;
    }

    // Then check the command byte to make sure response is what we were expecting
    if ( data[1] != 0x86 )
    {
        Serial.println("Error command");
        return false;
    }


    CO2PPM = (int)data[2] * 256 + (int)data[3];

    return true;
}
