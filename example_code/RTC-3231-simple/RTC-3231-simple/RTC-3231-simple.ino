#include "RTClib.h"

RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);
  rtc.begin();
}

void loop() {
 DateTime time = rtc.now();

 //Full Timestamp
 Serial.println(time.timestamp());

 //Serial.println("\n");

 //Delay 5s (5000 milliseconds)
 delay(5000);
}
