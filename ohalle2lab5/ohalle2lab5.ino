/*
   1- Author: Omkarnath Halleppanawar - 665916886
   2- Lab: Lab 5 - Communication 
   3- Description: Implements an even odd guessing game that lights up an led green or red whether you win or lose
   and points a servo propeller towards the corresponding led
   4-Lab Questions:
What does the myservo() function do? myservo is a servo object that is created to control the servo. In the code I use
the myservo.attach() function which attaches the servo on a certain pin to the servo object, and myservo.write() which
sets the servo position at the specified angle value. 
What are the angles of the servo motor for the three directions? red -> 90, neutral -> 45, green->20
What functions/methods did you use to take input? I used Serial.readString() and Serial.parseInt(), as well as
 Serial.available() to check if there is anything in the serial receive buffer
   5- References: resources given in the lab writeup
   6- Demo: in-person demonstration TA: Elijah Parr 10:00 AM 3/13/2023
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

const unsigned int MAX_MESSAGE_LENGTH = 12;
int num; // user inputted number
int parity; // 0 for even 1 for odd
int redPin = 6;
int greenPin = 3;
bool valid = true; // input is valid

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  //Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  randomSeed(analogRead(A0));
}
	
void loop() {
  valid = true; // reset for new game
  myservo.write(45); // neutral position
  digitalWrite(greenPin, 0); // reset for new game
  digitalWrite(redPin, 0); // reset for new game
  Serial.begin(9600);
  Serial.println("Welcome to Even Odd game!");
  Serial.println("Enter a number between 1 and 5!");
  while (Serial.available() == 0) {};
  while (Serial.available() > 0) {
    num = Serial.parseInt();
    if (num < 1 || num > 5) {
      valid = false; // invalid input
      Serial.println("Invalid input");
      break;
    }
    String message = "Received: " + String(num);
    Serial.println(message);
    Serial.end();
  }
  if (valid) {
    Serial.begin(9600);
    Serial.println("Enter even or odd!");
    while (Serial.available() == 0) {};
    while (Serial.available() > 0) {
      String input = Serial.readString();
      input.trim();
      String message = "Received: " + input;
      if (input == "even") {
        parity = 0;
      } else if (input == "odd") {
        parity = 1;
      } else {
        valid = false; // invalid input
        Serial.println("Invalid input");
        break;
      }
      Serial.println(message);
      //Serial.end();
    }
    if (valid) {
      Serial.println("Generating...");
      int randomNum = random(1, 5);
      
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      int sum = num + randomNum;
      String m1 = "My number: " + String(randomNum);
      String m2 = "Sum: " + String(sum);
      Serial.println(m1);
      Serial.println(m2);
      if (sum % 2 == parity) { // won game
        Serial.println("You win!");
        myservo.write(20);  
        digitalWrite(greenPin, 1); // light up green
      } else { // lost game
        Serial.println("You lose!");
        myservo.write(90);
        digitalWrite(redPin, 1); // light up red
      }
    }
  }
  Serial.end();
  delay(1000); // delay before new game

}
