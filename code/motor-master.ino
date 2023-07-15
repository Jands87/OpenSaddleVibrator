// Master code for Arduino Uno for the Saddle Vibrator
// https://www.thingiverse.com/thing:3554455
// Version 1.0 (14.4.19)

#include <Wire.h>

byte inData[10];                                 // incomming data array for data from controller (make larger than you need)

const int  motor0 = 3;                           // pin designation for motor 0
const int  motor1 = 5;                           // pin designation for motor 1
const int  LED = 13;                             // LED showing debugging mode

bool  button0 = 0;                               // internal variables for button 0 on controller
bool  button1 = 0;
bool  button1flag = 0;                           // check flag to see if button is being held down, debounce
bool  rampmode = 0;                              // flag for ramping mode on motor 0
bool  flag = 0;                                  // dead man switch for connection, stop motors if no data
bool  debugflag = 0;                             // set 1 for debugflag mode to print serial updates

void setup()
{
  delay(500);                                    // allow controller to start first
  Wire.begin();                                  // join i2c bus (address optional for master)
  Serial.begin(9600);                            // set serial baud to 9600
}

void loop() {

  flag = 0;                                      // set connection flag to off to show data to stop motors if no data arrives
  Wire.requestFrom(8, 5);                        // request 5 bytes from slave device #8
  while (Wire.available()) {
    for (int i = 0; i <= 4; i++) {
      inData[i] = Wire.read(); - '0';            // read 1 byte from the wire buffer in to "inData[i]"  -'0' is to convert back to int from char  
    }
    button0 = inData[2];                         // check to see if any buttons have been presed
    button1 = inData[3];
    
    if (inData [4] == 1){
      debugflag = 1;                             // enter debug mode
      digitalWrite(LED, HIGH);                   // LED showing debugging mode, HIGH);
    }
    else
    {
      debugflag = 0;                             // exit debug mode
      digitalWrite(LED, LOW);                    // LED showing debugging mode, HIGH);
    }
    
    flag = 1;                                    // set connection flag to on to show data has arrived.
  }

  if (flag == 0) {                               // deadman (no connection) switch to stop motors
    for (int i = inData[0]; i == 0; i--) {       // decrease motor 0 and 1 speeds until stopped
      analogWrite(motor0, 0);
      delay(10);
    }
    for (int i = inData[1]; i == 0; i--) {
      analogWrite(motor1, 0);
      delay(10);
    }
  }


  if (flag == 1) {                                // only continue if controller is connected (deadman switch check)

    // ***************** BUTTON 0 ROUTINES *****************

    if (button0 == 1) {                           // process button routine if button0 has been pressed
      button0press();
    }

    // ***************** BUTTON 1 ROUTINES *****************

    if (button1 == 1) {                           
      button1flag = 1;                            // set button flag to make sure it does not continuously run the routine (debounce)
    }

    if ((button1 == 0) && (button1flag == 1)) {   // if button has been released reset button0 flag and process routine
      button1flag = 0;
      if (rampmode == 0) {
        button1press();
      }
      else if (rampmode == 1) {
        rampmode = 0;
      }

    }

    // ****************** MOTOR  ROUTINES ******************

    if ((button0 == 0) && (button1 == 0)) {       // no buttons have been pressed - set motor speed
      if (rampmode == 1) {
        inData[0] = 255;
      }
      analogWrite(motor0, inData[0]);           // PWM to output motor 0 port
      delay(10);
      analogWrite(motor1, inData[1]);             // PWM to output motor 1 port
    }
  }
  if (debugflag == 1) {
    showSerial();
    delay(1000);
  }
  else if (debugflag == 0) {
    delay(100);
  }
}

void button0press() {                             // button0 has been pressed
  inData[0] = 255;                                // set motor0 speed to 100%
  analogWrite(motor0, inData[0]);                 // PWM to output motor 0 port
}

void button1press() {                             // button1 button has been pressed
  rampmode = 1;
  for (int i = inData[0]; i <= 255; i++) {            // slowly ramp motor speed to 100%
    Serial.print(i);
    Serial.println(".");
    analogWrite(motor0, i);
    delay(10);
  }
  Serial.println();
}

void showSerial() {
  Serial.print("Masterboard Status: ");
  if (flag == 0) {                                // deadman (no connection) switch to stop motors
    Serial.println("Controller disconnected. (Debugging)");
  }
  else if (flag == 1) {
    Serial.println("Controller connected. (Debugging)");
  }
  Serial.print("Motor 0:");
  Serial.print(inData[0]);
  Serial.print(" / ");
  Serial.print("Motor 1:");
  Serial.print(inData[1]);
  Serial.print(" / ");
  Serial.print("Button 0:");
  Serial.print(button0);
  Serial.print(" / ");
  Serial.print("Button 1:");
  Serial.print(button1);
  Serial.print(" / ");
  Serial.print("Button 1 Flag:");
  Serial.print(button1flag);
  Serial.print(" / ");
  Serial.print("Ramp Mode:");
  Serial.print(rampmode);

  Serial.println();
  Serial.println();
}
