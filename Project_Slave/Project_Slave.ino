#include <TimerOne.h>


// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int sen1=9;
int sen2=10;
int LEDred = 7;
int LEDgreen = 6;
int BUZZER_PIN = 8;
unsigned long t1=0;
unsigned long t2=0; 
float velocity = 0;
float speed = 0;
float velocityLimit = 30;
int on = 0;
void setup() {
  // set up the LCD's number of columns and rows:
  pinMode(sen1,INPUT);
  pinMode(sen2,INPUT);
  pinMode(LEDred, OUTPUT);
  pinMode(LEDgreen, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  
  if(Serial.available() > 0) {
    
    int i = Serial.read();
    Serial.println(i);
    //Serial.readStringUntil('\n');
    if (i == 0) {
      on = 0;
      lcd.clear();
      lcd.setCursor(7,0);
      lcd.print("OFF");
      
    }
    if (i == 1) {
      on = 1;
      digitalWrite(LEDgreen, HIGH);
      digitalWrite(LEDred, HIGH);
      analogWrite(BUZZER_PIN, 250);
      delay(550);
      analogWrite(BUZZER_PIN, 0);
      delay(550);
      analogWrite(BUZZER_PIN, 150);
      delay(550);
      analogWrite(BUZZER_PIN, 0);
      digitalWrite(LEDgreen, LOW);
      digitalWrite(LEDred, LOW);
    } else if (i != 0 && i != 1) {
      velocityLimit = i;
    }
    
  }
  
  if (on == 1 ) {

    
    lcd.setCursor(0,0);
    lcd.print("Speed Detector ");
    lcd.setCursor(0,1);
    lcd.print("Sp Limit: ");
    lcd.setCursor(9, 1);
    lcd.print(velocityLimit);

    while(digitalRead(sen1));
    while(digitalRead(sen1)==0);
    t1=millis();
    while(digitalRead(sen2));
    t2=millis();
    velocity=t2-t1;
    velocity=velocity/1000;//convert millisecond to second
    velocity=(0.165/velocity);//v=d/t
    velocity=velocity*3600;//multiply by seconds per hr
    speed=velocity/(1000*0.621371);//division by meters per Km
    if(speed < velocityLimit) {
      analogWrite(BUZZER_PIN, 250);
      delay(250);
      analogWrite(BUZZER_PIN, 0);
    }
    for(int i=0;i<8;i++)
    { 
      lcd.setCursor(6,0);
     lcd.print(speed);
     lcd.print(" mph");



      if (speed > velocityLimit) {
      
      digitalWrite(LEDred, HIGH);
      analogWrite(BUZZER_PIN, 250);
      delay(100);
      lcd.setCursor(6,0);
      lcd.print("            ");
      digitalWrite(LEDred, LOW);
      analogWrite(BUZZER_PIN, 0);
      } else {
        digitalWrite(LEDgreen, HIGH);
      }
     delay(100);

    }
    analogWrite(BUZZER_PIN, 0);
    digitalWrite(LEDgreen, LOW);
    
    
    //Serial.print(on);
    //Serial.readStringUntil('\n');
  }
}  
