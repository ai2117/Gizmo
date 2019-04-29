
// A big part of this code was taken from happythingsmaker EunChanPark
//This code was uploaded to the arduino of the master robot

#include <SoftwareSerial.h>



#define SW_SERIAL_TX     2 //Defining the digital port 2 as TX to connect HC-12

#define SW_SERIAL_RX     3 //Defining the digital port 3 as RX to connect HC-12



SoftwareSerial BTSerial(SW_SERIAL_RX, SW_SERIAL_TX); //Create software serial port



void setup() {

  Serial.begin(9600); //Open serial port to computer

  BTSerial.begin(9600); //Open serial port to HC-12

}



int tempADC = 0; //define value being read from the potentiometer

int adcPin[8] = {A0, A1, A2, A3, A4, A5, A6, A7}; //create a list defining each analogue input, each potentiometer (integers)

byte angle = 0; //define angle (byte)

void loop() {




  for (int id = 0; id < 8; id ++) { //for each potentiometer
    

    tempADC  = analogRead(adcPin[id]); //Read the value of the potentiometer
    
    tempADC  = min(842, tempADC); //transforming read values to the range of the servo motor (180 degrees) (potentiometer has a wider range)

    tempADC  = max(113, tempADC); //transforming read values to the range of the servo motor (180 degrees) (potentiometer has a wider range)

    angle = byte(map(tempADC, 113, 842, 0, 180)); //define the angle value from the mapped read value

    Serial.print(tempADC);
    Serial.print("     ");
    Serial.println(angle);


    delay(5); // needed



    BTSerial.write(255); //Send 255 through serial communication to prevent that information is going to be sent

    BTSerial.write(angle); //Send the angle value

    BTSerial.write(id); //Send what servo needs to be moved, i.e. the potentiometer id

  }

}
