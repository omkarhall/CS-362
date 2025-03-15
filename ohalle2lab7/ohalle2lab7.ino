/*
   1- Author: Omkarnath Halleppanawar - 665916886
   2- Lab: Lab 7 - Interrupts 
   3- Description: In your own words, what is this code supposed to do?
   This program is a guessing game where a random number is assigned each game, and the player clicks a button
   when the number shows up on the 7 segment display to win
   4-Lab Questions:
What is the purpose of a current-limiting resistor in a seven-segment display circuit? 
  They protect the display from being damaged by overcurrent
Can you display special characters? If yes, How?
  Yes, each LED segment of the display can be lit up independently. If you only light up certain segments
  you can display special characters
What are some common applications of seven-segment displays?
  Countdown clocks, such as  NASA’s countdown clock at Cape Canaveral, Florida are applications of seven-segment displays
  They are also used in appliances, such as microwaves and ovens.
   5- References: https://www.allaboutcircuits.com/technical-articles/using-interrupts-on-arduino/
   6- Demo: in-person demonstration 4/10/2023 10:35 Elijah Parr
*/
#include <SevSeg.h>

SevSeg sevseg;
int buttonPin = 2;
int buttonNew;
int buttonOld = 1;

bool newGame = true; // new game or not
volatile bool win = false; // won game
volatile bool lose = false; // lost game
bool firstGame = true; // first time playing
int i; // counter for display
int randomNum; // random number for each game

void setup() {
  // Set to 1 for single digit display
	byte numDigits = 1;

	//defines common pins while using multi-digit display. Left empty as we have a single digit display
	byte digitPins[] = {};

	//Defines arduino pin connections in order: A, B, C, D, E, F, G, DP
	byte segmentPins[] = {4, 3, 9, 8, 7, 5, 6, 10};
	bool resistorsOnSegments = true;

	//Initialize sevseg object. Uncomment second line if you use common cathode 7 segment
	sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);

	sevseg.setBrightness(90);
  attachInterrupt(digitalPinToInterrupt(buttonPin), checkWinner, RISING);
  pinMode(buttonPin, INPUT);
  randomSeed(analogRead(A0));
  Serial.begin(9600);
}

void loop() {
  // new game has started
  if (newGame) {
    i = 0; // reset display
    randomNum = random(0,9); // new random number
    String s = "The selected random number is: " + String(randomNum);
    Serial.println(s);
    newGame = false;
  }
  if (i == 10) {
    i = 0;
  }
  //Display numbers one by one with 0.5 seconds delay
  sevseg.setNumber(i);
  sevseg.refreshDisplay(); 
  delay(500);
  if (win == true) { // game won
    Serial.println("Congratulations! You pressed at the correct number.");
    Serial.println("The game is restarting...");
    newGame = true;
    win = false;
  }
  if (lose == true) { // game lost
    Serial.println("Oops! You stopped at the wrong number. Resuming the game.");
    lose = false;      
  }
  i++;
}

void checkWinner() {
  if (i == randomNum) { // number clicked matches display
    win = true;
  } else {
    lose = true;
  }
}
