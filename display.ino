#include <LiquidCrystal.h>

// LCD pin to Arduino
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7;

// Stepper
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 200

//Parametros
int flujo = 10;
int vueltas = 0;

const int pin_BL = 10; 

LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

void setup() {
  /* ========== Display ========== */
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Bomba Infusion");
  lcd.setCursor(0,1);
  lcd.print("Flujo:");
  lcd.setCursor(10,1);
  lcd.print("ml/min");

  /* ========== Stepper ========== */
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  int x;
  x = analogRead (0);
  lcd.setCursor(7,1);
  lcd.print(flujo);
  
  if(flujo < 10){
    lcd.setCursor(8,1);
    lcd.print(" ");
  }
  
  if (x < 200) {
    flujo++;
    delay(200);
  }
  else if (x < 400){
    flujo--;
    delay(200);
  }
  else if (x < 600){
    restart();
  }
  else if (x < 800){
    bomba();
  }
}

void bomba(){
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);
  int flag = 10;
  
  while ( flag > 0){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
    flag--;
  }
}

void restart(){
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, LOW);
  int flag = 10;
  
  while ( flag > 0){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
    flag--;
  }
}
