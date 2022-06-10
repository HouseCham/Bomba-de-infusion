#include <AccelStepper.h>
#include <LiquidCrystal.h>

AccelStepper stepper = AccelStepper(1, 3, 2);

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
int pasosPorVuelta;

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

  stepper.setMaxSpeed(208);
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
  stepper.setCurrentPosition(0);

  switch(flujo){
    case 1:
      pasosPorVuelta = 845;
      break;
    case 2:
      pasosPorVuelta = 820;
      break;
    case 3:
      pasosPorVuelta = 825;
      break;
    case 4:
      pasosPorVuelta = 815;
      break;
    case 8:
      pasosPorVuelta = 790;
      break;
     default:
      pasosPorVuelta = 800;
      break;
  }
  
  int pasosCount = pasosPorVuelta * flujo;

  while(stepper.currentPosition() != pasosCount) 
  {
    stepper.setSpeed(pasosCount/60);
    stepper.runSpeed();
  }
}

void restart(){
  stepper.setCurrentPosition(0);
  
  while(stepper.currentPosition() != -200) 
  {
    stepper.setSpeed(-600);
    stepper.runSpeed();
  }
}
