/*
The circuit:
  * LCD RS pin to digital pin 12
  * LCD Enable pin to digital pin 11
  * LCD D4 pin to digital pin 5
  * LCD D5 pin to digital pin 4
  * LCD D6 pin to digital pin 3
  * LCD D7 pin to digital pin 2
  * LCD R/W pin to ground
  * LCD VSS pin to ground
  * LCD VCC pin to 5V
  * 10K resistor:
  * ends to +5V and ground
  * wiper to LCD VO pin (pin 3)

  on/off button to pin 13
  speed limit increment button to pin 7
  speed limit send button to pin 9

  // Project Master
  Code for the remote subsystem that controls the IR subsystem
  * Turns IR subsystem on/off
  * Changes speed limit for IR subsystem

  Resources: none
*/

#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int buttonPin1 = 13; // turn on/off 
int buttonNew1;
int buttonOld1 = 1;

int buttonPin2 = 7; // speed limit
int buttonNew2;
int buttonOld2 = 1;

int buttonPin3 = 9; // confirm speed limit
int buttonNew3;
int buttonOld3 = 1;

int redPin = 6; // red led pin
int greenPin = 8; // green led pin

int remoteOn = 0; // 0 for off 1 for on
int limit = 0; // speed limit

void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  // starting display
  lcd.setCursor(1,0);
  lcd.print("Maha Detector:");
  lcd.setCursor(7,1);
  lcd.print("Off");
  digitalWrite(redPin, 1);
}

void loop() {
  buttonNew1 = digitalRead(buttonPin1);
  buttonNew2 = digitalRead(buttonPin2);
  buttonNew3 = digitalRead(buttonPin3);
  if (buttonOld1 == 0 && buttonNew1 == 1) {
    if (remoteOn == 0) { // turn IR detector on
      remoteOn = 1;
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Maha Detector:");
      lcd.setCursor(7,1);
      lcd.print("On");
      digitalWrite(greenPin, 1);
      digitalWrite(redPin, 0);
      Serial.write(remoteOn);
    } else { // turn IR detector off
      remoteOn = 0;
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Maha Detector:");
      lcd.setCursor(7, 1);
      lcd.print("Off");
      digitalWrite(greenPin, 0);
      digitalWrite(redPin, 1);
      Serial.write(remoteOn);
    }
  }
  buttonOld1 = buttonNew1;

  if (buttonOld2 == 0 && buttonNew2 == 1 && remoteOn > 0) {
    limit = limit + 1; // increment speed limit and display it
    lcd.setCursor(1, 1);
    lcd.print("Speed = ");
    lcd.setCursor(9, 1);
    String s = String(limit) + " mph";
    lcd.print(s);
  }
  buttonOld2 = buttonNew2;

  if (buttonOld3 == 0 && buttonNew3 == 1 && remoteOn > 0) {
    Serial.write(limit); // send new speed limit
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Maha Detector:"); // reset lcd screen
    lcd.setCursor(7,1);
    lcd.print("On");
    limit = 0; // reset limit
  }
  buttonOld3 = buttonNew3;
  delay(50);
}


