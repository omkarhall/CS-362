/*
   1- Author: Omkarnath Halleppanawar (as shown in Blackboard) - 665916886
   2- Lab: Lab 2 - The LCD 
   3- Description: A 2 player racing game that is controlled by 2 buttons and is displayed on the LCD
   4- LCD Pins: List what each of the following LCD pins are for, i.e. “D4: Data pin 4”. (Read the prelab)
     VSS(GND): GND
     VDD(+5V): 5V
     V0: Potentiometer
     RS: Digital pin 12
     RW: GND
     E(Enable): Digital pin 11
     D4: Digital pin 5
     D5: Digital pin 4
     D6: Digital pin 3
     D7: Digital pin 2
     A(BKlt+): LED+
     K(BKlt-): LED-
   5- References: Given assignment writeup and the video linked in the assignment
   6- Demo: In person demonstration, TA: Elijah Parr Time 10:20 AM Date 2/06/2023
*/

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int buttonPin1 = 9;
int buttonNew1;
int buttonOld1 = 1;

int buttonPin2 = 10;
int buttonNew2;
int buttonOld2 = 1;

int newGame = 0; // tracks whether a new game has started or not
// tracks position of both players
int x1 = 0;
int x2 = 0;
// tracks which lap the player is on
int p1_lap = 1;
int p2_lap = 1;
	
void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Player 1 ($)");
  lcd.setCursor(0,1);
  lcd.print("Player 2 (&)");
}

void loop() {
  buttonNew1 = digitalRead(buttonPin1);
  if (buttonOld1 == 0 && buttonNew1 == 1) {
    if (newGame == 0) { // new game has started
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("$");
      lcd.setCursor(0,1);
      lcd.print("&");
      newGame = 1;
    } else {
      lcd.setCursor(x1, 0);
      lcd.print(" ");
      x1 = x1 + 1;
      lcd.setCursor(x1, 0);
      lcd.print("$");
      if (x1 == 16) { // player 1 reached end of first lap
        p1_lap = 2;
        x1 = 0;
        lcd.setCursor(0, 0);
        lcd.print("$");
        lcd.setCursor(15, 0);
        lcd.print("#");
      }
      if (p1_lap == 2) {  // second lap has started
        if (x1 == 15) { // reached end of second lap
          lcd.clear();
          lcd.print("Player 1 Wins!");
          // reset for new game
          x1 = 0;
          x2 = 0;
          p1_lap = 1;
          p2_lap = 1;
          newGame = 0;
          delay(1000);
          lcd.clear();
          lcd.print("Player 1 ($)");
          lcd.setCursor(0,1);
          lcd.print("Player 2 (&)");
        }
      }
    }
  }
  buttonOld1 = buttonNew1;


  buttonNew2 = digitalRead(buttonPin2);
  if (buttonOld2 == 0 && buttonNew2 == 1) {
    if (newGame == 0) { // new game has started
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("$");
      lcd.setCursor(0,1);
      lcd.print("&");
      newGame = 1;
    } else {
      lcd.setCursor(x2, 1);
      lcd.print(" ");
      x2 = x2 + 1;
      lcd.setCursor(x2, 1);
      lcd.print("&");
      if (x2 == 16) { // player 2 reached end of first lap
        p2_lap = 2;
        x2 = 0;
        lcd.setCursor(0, 1);
        lcd.print("&");
        lcd.setCursor(15, 1);
        lcd.print("#");
      }
      if (p2_lap == 2) { // second lap has started
        if (x2 == 15) { // player 2 reached end of second lap
          lcd.clear();
          lcd.print("Player 2 Wins!");
          // reset for new game
          x1 = 0;
          x2 = 0;
          p1_lap = 1;
          p2_lap = 1;
          newGame = 0;
          delay(1000);
          lcd.clear();
          lcd.print("Player 1 ($)");
          lcd.setCursor(0,1);
          lcd.print("Player 2 (&)");
        }
      }
    }
  }
  buttonOld2 = buttonNew2;
}

