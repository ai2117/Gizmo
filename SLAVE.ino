
// A big part of this code was taken from happythingsmaker EunChanPark
//This code was uploaded to the arduino of the slave robot

#include <Adafruit_PWMServoDriver.h>  //library to use the PWM driver

#include <SoftwareSerial.h>



#define SW_SERIAL_TX     2  //Defining the digital port 2 as TX to connect HC-12

#define SW_SERIAL_RX     3 //Defining the digital port 3 as RX to connect HC-12


Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver(0x40); // 0x40 is the ID of the PWM driver

SoftwareSerial BTSerial(SW_SERIAL_RX, SW_SERIAL_TX); //Create software serial port


void setup() {

  Serial.begin(9600); //Open serial port to computer
  BTSerial.begin(9600); //Open serial port to HC-12



  pwmDriver.begin(); // Begin the driver

  pwmDriver.setPWMFreq(51); // the PWM driver's frequency is 50 Hz and we need to add 1

  pwmDriver.setPWM(0, 0, 500);  // setPWM(ID, on Time, off Time out of 4096)

}



byte tempID = 0; // ID of the potentiometer that is being moved (variable)

byte tempAngle = 0; // Angular position





void loop() {
  while (BTSerial.available() > 3) {  //while the serial communication is available (port 3)
    if (BTSerial.read() == 255) { //if information has been sent
      tempAngle = BTSerial.read(); //Read the angular position of the potentiometer that has been sent through serial communication
      tempID = BTSerial.read(); //Read the ID of the potentiometer that has been sent through serial communication
    
      pwmDriver.setPWM(tempID, 0, map(tempAngle, 0, 180, 111, 491)); // Send the ID value to the driver, to let it know what servos must move, and their angular position

    }

  }
}
