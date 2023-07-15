// Master code for Arduino Uno for the Saddle Vibrator by Jands
// https://www.thingiverse.com/thing:3554455
// Version 1.0 (14.4.19)

#include <Wire.h>

const int pot0 = A0;              // pin designation for pot 0
const int pot1 = A1;              // pin designation for pot 1
const int butt0 = 2;              // pin designation for button 0
const int butt1 = 3;              // pin designation for button 1
const int  LED = 13;              // LED showing debugging mode

byte motor0;
byte motor1;
byte button0;
byte button1;
byte debugflag;

void setup()
{
  Wire.begin(8);                  // join i2c bus with address #8
  Wire.onRequest(requestEvent);   // register event

  Serial.begin(9600);             // set serial baud to 9600
  Serial.println("Slave");        // print on screen position of board

  pinMode(butt0, INPUT_PULLUP);   // set both inputs to internal pull ups
  pinMode(butt1, INPUT_PULLUP);
}

void loop()
{
  motor0 = map(analogRead(pot0), 0, 1023, 0, 255);  // map will return byte size data
  delay(10);
  motor1 = map(analogRead(pot1), 0, 1023, 0, 255);
  button0 = !digitalRead(butt0);                    // read in button status and invert
  button1 = !digitalRead(butt1);
  delay(100);                      // 0.1-sec interval as a test interval

  if ((digitalRead(butt0) == 0) && (digitalRead(butt1) == 0)) {   // enter debug mode if both buttons pressed when powered on
    if (debugflag == 0) {
      debugflag = 1;
      digitalWrite(LED, HIGH);
      button0 = 0;
      button1 = 0;
      delay(1000);
    }
    else {
      debugflag = 0;
      digitalWrite(LED, LOW);
      button0 = 0;
      button1 = 0;
      delay(1000);
    }
  }
}

void requestEvent()
{
  Wire.write(motor0);              // data item-1 as ASCII codes
  Wire.write(motor1);              // data item-2 as ASCII codes
  Wire.write(button0);             // data item-3 as ASCII codes
  Wire.write(button1);             // data item-3 as ASCII codes
  Wire.write(debugflag);           // data item-3 as ASCII codes

  if (debugflag == 1) {
    Serial.print(motor0);            // data item-1 as ASCII codes
    Serial.print(",");               // local seperator
    Serial.print(motor1);            // data item-2 as ASCII codes
    Serial.print(",");               // local seperator
    Serial.print(button0);           // data item-3 as ASCII codes
    Serial.print(",");               // local seperator
    Serial.print(button1);           // data item-3 as ASCII codes
    Serial.print(",");               // local seperator
    Serial.println(debugflag);       // display debug status
  }
}
