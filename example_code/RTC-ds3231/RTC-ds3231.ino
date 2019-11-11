// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"

//RTC_DS3231 rtc;
RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {
  Serial.begin(9600);
  //delay(3000); // wait for console opening

  if (! rtc.begin()) {
    while (1);
  }

  
}

int t;
void loop () {
    DateTime now = rtc.now();
    
    t = Serial.println();
    
    delay(3000);
}
