// single line comment uses '//'
/* multi-line comment uses '/*
 *  this is a multi-line comment
 */

int ledPIN = 13; 
/* Above is an example of how to declare variables 
 * Here, I declared an integer variable called 'ledPIN' 
 * and I assigned it a value of 13.
 * The ledPIN variable represents pin 13 in the Arduino
 */


void setup() {
  /* This chunk of code is called a 'method'. 
   * It sets up code that will only run once.
   * Put your setup code here, to run once: 
   */

   // Initialize pins in your Arduino as outputs
   pinMode(ledPIN, OUTPUT); 
   /* pinMode requires 2 arguments: 
    *  1. the pin
    *  2. whether the pin will be used as an INPUT or OUTPUT
    */

}

void loop() {
  /* This chunk of code is also a 'method'. 
   * It sets up code that will run repeatedly until you turn it off.
   * Put your main code here, to run repeatedly.
   * This method can be also be empty if you do not need it.
   */
   digitalWrite(ledPIN, HIGH); // Turns the LED light on pin 13 on
   delay(1000); // Keeps the LED light on for 1000 milliseconds (1 second)
   digitalWrite(ledPIN, LOW); // Turns the LED on pin 13 off
   delay(1000); // Keeps the LED light off for 1000 milliseconds (1 second)

}
