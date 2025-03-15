/*
   1- Author: Omkarnath Halleppanawar - 665916886

   2- Lab: Lab 3 - Analog Signals 

   3- Description: A game where a player is moving back and forth across the LCD and trying to click a button to land on a platform

   4- Lab Questions:
        What contrast number did you pick for your LCD? -> 130
        What was the smallest potentiometer value you were able to beat the game on? -> 89
        What is the difference between an analog and PWM signal? -> PWM signals can only be 0 or 1 while analog signals have a greater range of possible values

   5- References: Lab 3 writeup and resources given in writeup

   6- Demo: In person demonstration: Elijah Parr 2/20 10:00 AM
*/

// chose 130 as contrast value
// red led to pin 8
// green led to pin 9
// button to pin 13

#include <LiquidCrystal.h>

// If you use a different pin for your wiring, make sure it is a PWM pin (~)
// and replace 6 with the pin you used.
#define CONTRAST_PIN 6

// MAKE SURE THESE PINS MATCH YOUR WIRING!!!
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte block[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

byte player[8] = {
	0b00000,
	0b00000,
	0b00000,
	0b11111,
	0b10101,
	0b11111,
	0b10101,
	0b10101
};

int buttonPin = 13;
int buttonNew;
int buttonOld = 1;
int redPin = 8;
int greenPin = 9;
int direction = 0; // 0 means go right, 1 means go left
int pos = 0; // position of player
bool pause = false; // button clicked -> pause screen

void setup() {
  pinMode(CONTRAST_PIN, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  lcd.begin(16, 2);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // TODO: When you have a contrast value you want to try, put this line of code
  // into your setup function and replace <VALUE> with the contrast value that you picked (between 0 and 255).
  //
  analogWrite(CONTRAST_PIN, 130);
    
  lcd.createChar(0, block); // create a new custom character
  lcd.createChar(1, player); // create a new custom character
  for (int i = 6; i < 10; i++) {
    lcd.setCursor(i, 1); // move cursor
    lcd.write((byte)0);  // print the custom char
  }
  lcd.setCursor(0, 0);
  lcd.write((byte)1);  // print the custom char
}



// This code will loop through every contrast value on an LCD screen
// while displaying a message, so that you can figure out what value
// to set the contrast on your display to.
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(1);  // delay in between reads for stability

  if (!pause) {
    if (direction == 0) { // move player across right
      lcd.setCursor(pos, 0);
      lcd.print(" ");
      pos++;
      lcd.setCursor(pos, 0);
      lcd.write((byte)1);
      if (pos == 15) { // edge of screen
        direction = 1; // go left
      }
    } else { // move player across left
      lcd.setCursor(pos, 0);
      lcd.print(" ");
      pos--;
      lcd.setCursor(pos, 0);
      lcd.write((byte)1);
      if (pos == 0) { // edge of screen
        direction = 0; // go right
      }
    }
    delay(sensorValue);
  }

  buttonNew = digitalRead(buttonPin);
  if (buttonOld == 0 && buttonNew == 1) {
    pause = true; // stop moving player
    if (pos >= 6 && pos <= 9) { // landed on platform
      delay(2000);
      digitalWrite(greenPin, HIGH);
      lcd.clear();
      lcd.print("You Win!");
    } else { // landed off platform
      delay(2000);
      digitalWrite(redPin, HIGH);
      lcd.clear();
      lcd.print("You Lose!");
    }
    // reset game
    delay(2000);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    lcd.clear();
    direction = 0;
    pause = false;
    pos = 0;
    for (int i = 6; i < 10; i++) {
      lcd.setCursor(i, 1); // move cursor
      lcd.write((byte)0);  // print the custom char
    }
    lcd.setCursor(0, 0);
    lcd.write((byte)1);  // print the custom char
  }
  buttonOld = buttonNew;
}
