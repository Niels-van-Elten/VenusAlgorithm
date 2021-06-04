#include <Arduino.h>
#include <Servo.h>                           // Include servo library
  
Servo servoLeft;                             // Declare left servo signal
Servo servoRight;                            // Declare right servo signal
Servo servoGripper;   
Servo servoHead;
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
   servoHead.attack();
   Serial.begin(9600);

// start with standing still // 

  stand_still();
 
} 
void loop() {
long duration, USM;
  void DistanceUSM(){
    long duration, cm;

    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    pinMode(9, OUTPUT);
    digitalWrite(9, LOW);
    delayMicroseconds(2);
    digitalWrite(9, HIGH);
    delayMicroseconds(5);
    digitalWrite(9, LOW);

    // The same pin is used to read the signal from the PING))): a HIGH pulse
    // whose duration is the time (in microseconds) from the sending of the ping
    // to the reception of its echo off of an object.
    pinMode(9, INPUT);
    duration = pulseIn(9, HIGH);

    // convert the time into a distance
    USM = microsecondsToCentimeters(duration);

    delay(30);
    return(USM)
  }


  
  while((USM>5) && ((IRL > 500) || (IRR > 500))){
    servoLeft.writeMicroseconds(LF);         //Turn right untill it sees the lab wall
    servoRight.writeMicroseconds(RB);
    delay(100);
    stand_still();
    USM=DistanceUSM();
    IRL=ColourIRL();
    IRR=ColourIRR();
  }

  while((USM<100) && ((IRL > 500) || (IRR > 500))){
    servoLeft.writeMicroseconds(LF);         //Turn right untill robot is parallel to the wall
    servoRight.writeMicroseconds(RB);
    delay(100);
    stand_still();
    USM=DistanceUSM();
    IRL=ColourIRL();
    IRR=ColourIRR();
  }
  stand_still();
  servoHead.write(0);                   //Now the robot's body is parallel to the lab wall and the head is looking at the wall
      
    while((USM<10) && (USM>5) && ((IRL > 500) || (IRR > 500))){
      servoLeft.writeMicroseconds(LF);    //Drive forward untill it either gets too close to the wall or strays away too far from the wall
      servoRight.writeMicroseconds(RF);
      delay(100);
      stand_still();
      USM=DistanceUSM();
      IRL=ColourIRL();
      IRR=ColourIRR();
    }
    stand_still();
    while((USM<5) && ((IRL > 500) || (IRR > 500))){
      servoLeft.writeMicroseconds(LF);         //If the robot gets too close to the wall turn right
      servoRight.writeMicroseconds(RB);
      delay(100);
      stand_still();
      USM=DistanceUSM();
      IRL=ColourIRL();
      IRR=ColourIRR();
    }
    stand_still();
    while((USM>10) && ((IRL > 500) || (IRR > 500)))
      servoLeft.writeMicroseconds(LB);         //If the robot gets too far from the wall turn left
      servoRight.writeMicroseconds(RF);
      delay(100);
      stand_still();
      USM=DistanceUSM();
      IRL=ColourIRL();
      IRR=ColourIRR();
  }
  open_gripper()             //Drop sample when he sees black tape during this manouvre
  returns +=1
}
