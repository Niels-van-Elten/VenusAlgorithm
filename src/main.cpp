/*
 Robotics with the BOE Shield – ServoRunTimes
 Generate a servo full speed counterclockwise signal with pin 13 and 
 full speed clockwise signal with pin 12.
 */
// Declarations //

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Arduino.h>
#include <Servo.h>                           // Include servo library

#define echoPin 4 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 5 //attach pin D3 Arduino to pin Trig of HC-SR04


Servo servoLeft;                             // Declare left servo signal
Servo servoRight;                            // Declare right servo signal
Servo servoGripper;   

const int analogInPin = A0;  // Analog input pin that the receiver is attached to
int sensorValue = 0;        // value read from the receiver
int incomingByte;
long duration; // variable for the duration of sound wave travel
int USH; // variable for the distance measurement
   
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
  pinMode(13, OUTPUT);                       //initialize the indicator LED:
  pinMode(trigPin, OUTPUT);                  // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);                   // Sets the echoPin as an INPUT
  Serial.begin(9600);
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  // start with standing still // 

  stand_still();
 
}  
 
void loop(){                                  // Main loop auto-repeats
  //Infrared sensor code
  // read the analog in value:
  IRL = analogRead(analogInPin);

  // print the results to the serial monitor:
  Serial.print("\nsensor = ");
  Serial.print(IRL);
  //the threshold found fron analog In Out program was when object is detected, the sensor value is below 100
  //set the threshold whihc you get
  //the threshold varies for different sets of emitter-receiver pairs
  if(IRL < 100){ //checks if object is there or not
    digitalWrite(13, HIGH);
    Serial.print("\nObject Detected");
  }
  else{
    digitalWrite(13, LOW);
    Serial.print("\nNo object in Front");
  }

  delay(200);

  //Ultrasound code

  long duration, USM;

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

  Serial.print("Distance middle sensor:");
  Serial.print(USM);

  Serial.println();

  delay(30);

  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  USH = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance upper sensor: ");
  //upper sensor code is the same has bottom sensor code 
  Serial.print(USH);
  Serial.println(" cm");
  delay(600);
  
  long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we  
  // take half of the distance travelled.
  return microseconds / 28.65 / 2;

  //Mountain evasion

  srand(time(0));                             // Creates new rand seed
  
  if(USH>=100){                         // Turns to the right by random amount
    turn_right(rand()/10000000);

  }

  if(IRL>=100){                         // Turns to the right by random amount
    turn_right(rand()/10000000);

  }

  /*
  if(IRR>=100){                         // Turns to the right by random amount
    turn_right(rand()/10000000);

  }
  */

}