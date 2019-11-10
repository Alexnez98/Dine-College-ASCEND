#include <SPI.h>

#include <SD.h>
int uv_ain=A0;
int ad_value;




File logFile;

char fileName[] = "logFile.csv";

const uint8_t chipSelect = 10;

const uint8_t cardDetect = 9;

bool alreadyBegan = false;

void setup()
{
  
  Serial.begin(9600);
  pinMode(uv_ain,INPUT);
  pinMode(cardDetect, INPUT);



    logFile = SD.open(fileName, FILE_WRITE);

    if(logFile) {

        logFile.println("x,y,z,#");

        for(int i = -50; i < 50; i++){

            logFile.print(pow(i,1));

            logFile.print(',');

            logFile.print(pow(i,2));

            logFile.print(',');

            logFile.print(pow(i,3));

            logFile.print(',');

            logFile.println(millis());

        }

        logFile.close();

    }

    else{

        Serial.println(F("Failed to open file"));

    }



}

void loop()
{
  ad_value=analogRead(uv_ain);
  if(ad_value>20)
  {
    Serial.println("UV up the standard");

  
  }
  else
  {
    Serial.println("UV down the standard");
  }
 

Serial.print(ad_value);

    logFile = SD.open("startup.csv", FILE_WRITE);

    if (logFile) {

        logFile.print(4);

        logFile.print(',');

        logFile.print(2);

        logFile.print(',');

        logFile.print(0);

        logFile.print(',');

        logFile.println(millis());

        logFile.close();

    }

    else{

        Serial.println(F("Failed to open file"));

    }
 delay(1000);
}
