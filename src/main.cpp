/*
 Robotics with the BOE Shield – ServoRunTimes
 Generate a servo full speed counterclockwise signal with pin 13 and 
 full speed clockwise signal with pin 12.
 */
// Declarations //

#include <Arduino.h>
#include <Servo.h>                           // Include servo library
  
Servo servoLeft;                             // Declare left servo signal
Servo servoRight;                            // Declare right servo signal
Servo servoGripper;   

int incomingByte;

   
   // Pulse widths 
   
   int LF = 1520;            // Left forward
   int LB = 1360;            // Left backward
   int RF = 1300;            // Right forward
   int RB = 1620;            // Right backward
   int S = 1460;            // Stand still

// Declarations end//

// Functions //

void drive_forward(int d){
  servoLeft.writeMicroseconds(LF);          
  servoRight.writeMicroseconds(RF);       
  delay(d);                               
}

void drive_backward(int d){
  servoLeft.writeMicroseconds(LB);         
  servoRight.writeMicroseconds(RB);        
  delay(d);                              
}

void turn_left(int d){
  servoLeft.writeMicroseconds(LB);         
  servoRight.writeMicroseconds(RF);        
  delay(d);  
}

void turn_left_one_wheel(int d){
  servoLeft.writeMicroseconds(S);         
  servoRight.writeMicroseconds(RF);        
  delay(d); 
}

void turn_right(int d){
  servoLeft.writeMicroseconds(LF);         
  servoRight.writeMicroseconds(RB);        
  delay(d); 
}

void turn_right_one_wheel(int d){
  servoLeft.writeMicroseconds(LF);         
  servoRight.writeMicroseconds(S);        
  delay(d); 
}

void stand_still(){
   servoLeft.writeMicroseconds(S);         
   servoRight.writeMicroseconds(S);         
}

void open_gripper(){
  servoGripper.write(60);
}

void close_gripper(){
  servoGripper.write(120);
}

//Functions end//

void setup()                                 // Built in initialization block
{ 

// setup //

   servoLeft.attach(13);                      // Attach left signal to P13 
   servoRight.attach(12);                     // Attach right signal to P12   
   servoGripper.attach(10);

   Serial.begin(9600);

// start with standing still // 

  stand_still();
 
}  
 
void loop()                                  // Main loop auto-repeats
{                                            

 // see if there's incoming serial data:

  if (Serial.available() > 0) {

    // read the oldest byte in the serial buffer:

    incomingByte = Serial.read();

// if-statements for every function//

    if (incomingByte == 'F') {

      drive_forward(3000);
     }

     if (incomingByte == 'B') {

      drive_backward(3000);
     }

     if (incomingByte == 'L') {

      turn_left(650);
     }

     if (incomingByte == 'I') {

      turn_left_one_wheel(1070);
     }

     if (incomingByte == 'R') {

      turn_right(680);
     }

     if (incomingByte == 'P') {

      turn_right_one_wheel(1070);
     }

     if (incomingByte == 'S') {

      stand_still();
     }

     if (incomingByte == 'O') {

      open_gripper();
     }

     if (incomingByte == 'C') {

      close_gripper();
     }

     
  }


// End with standing still //

stand_still();

}