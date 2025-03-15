
/*
   1- Author: Omkarnath Halleppanawar - 665916886
   2- Lab: Lab 1 - Toggle Button
   3- Description: Code simulates an and gate that lights up LED when both input LEDs are on
   4- PIN numbers: Pin 7 and 10 are connected to blue LEDs which is output, Pin 8 and pin 13 are connected to buttons which is input
   and pin 12 is connected to red LED which is output
   5- References: Lab writeup, youtube video given in lab writeup
   6- Demo: In-person demonstration, 1/30/2023 TA: Judhajit time 10:50 AM
*/

int ledState1 = 0;
int ledPin1 = 7;
int buttonPin1 = 8;
int buttonNew1;
int buttonOld1 = 1;

int ledState2 = 0;
int ledPin2 = 10;
int buttonPin2 = 13;
int buttonNew2;
int buttonOld2 = 1;

int redPin = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(redPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  buttonNew1 = digitalRead(buttonPin1);
  if (buttonOld1 == 0 && buttonNew1 == 1) {
    if (ledState1 == 0) {
     digitalWrite(ledPin1, 1);
     ledState1 = 1;
    } else {
      digitalWrite(ledPin1, 0);
      ledState1 = 0;
    }
  }
  buttonOld1 = buttonNew1;


  buttonNew2 = digitalRead(buttonPin2);
  if (buttonOld2 == 0 && buttonNew2 == 1) {
    if (ledState2 == 0) {
     digitalWrite(ledPin2, 1);
     ledState2 = 1;
    } else {
      digitalWrite(ledPin2, 0);
      ledState2 = 0;
    }
  }
  buttonOld2 = buttonNew2;


  if (ledState1 == 1 && ledState2 == 1) {
    digitalWrite(redPin, 1);
  } else {
    digitalWrite(redPin, 0);
  }
}
