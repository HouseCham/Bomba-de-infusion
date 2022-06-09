#include <LiquidCrystal.h>

// LCD pin to Arduino
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7;

// Valores bomba
const int delayMin = 38461;
const int delayMax = 2400;
const int pasosPorVuelta = 780;

// Stepper
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 200

//Parametros
int flujo = 1;
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
    if(flujo < 16){
      flujo++;
      delay(200); 
    }
  }
  else if (x < 400){
    if(flujo > 1){
      flujo--;
      delay(200); 
    }
  }
  else if (x < 600){
    restart();
  }
  else if (x < 800){
    bomba(flujo);
  }
}

void bomba(int flujo){
  int pasosCount = pasosPorVuelta * flujo;
  int delayBomba = (delayMin * pasosPorVuelta)/ pasosCount;
  
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);
  bool flag = true;
  while(flag){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(37974);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(37974);
    pasosCount--;
    if(pasosCount < 0){
      flag = false;
    }
  }
}

void restart(){
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, LOW);
  bool flag = true;
  int count = 0;
  
  while(flag){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
    count++;
    if(count > 800){
      flag = false;
    }
  }
}
