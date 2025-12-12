#include <LiquidCrystal_I2C.h>

//Configuración componentes
	//LCD
LiquidCrystal_I2C lcd(0x20,16,2); //16 letras, 2 filas 
								 // 4 numeros 12 extra (Eq1, Eq2), "a" a mitad, etc.
	//LEDS
const int ledTeam1 =3;
const int ledTeam2 =4;
	//Buzzer
const int buzzer=5; 
	//Pulsadores
const int Team1=0; 
const int Team2=0; 

//variables
int pointTeam1=3;
int pointTeam2=12;

// --- Variables para pulsación larga/corta ---
unsigned long pressTeam1 = 0;
unsigned long pressTeam2 = 0;

bool lastState1 = HIGH;  
bool lastState2 = HIGH;

const unsigned long longPressTime = 700;  // 700 ms → pulsación larga

//Functions
void SumarTeam1(int);
void SumarTeam2(int);
void RestarTeam1(int);
void RestarTeam2(int);
void ControlTeam1();
void ControlTeam2();
void WritePoints(int, int);

void setup()
{
  
  pinMode(Team1, INPUT_PULLUP);
  pinMode(Team2, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT); 
  
  lcd.init();   
  lcd.backlight();
  lcd.setCursor(0, 0); 
  lcd.print("Empieza");
  lcd.setCursor(0, 1);
  lcd.print("el partido!");
  delay(2000);
  lcd.clear();  //ACORDAROS DE ESTA LINEA, SIRVE PARA LIMPIAR LA PANTALLA ANTES DE AÑADIR MÁS COSAS O NUEVAS
   WritePoints(pointTeam1, pointTeam2);
}

void loop()
{
 ControlTeam1();
 ControlTeam2();  
}

void SumarTeam1(int pts){
  pointTeam1+=pts;
  WritePoints(pointTeam1, pointTeam2);
  tone(buzzer, 800, 80);
}

void RestarTeam1(int pts){
  if (pointTeam1 > 0) pointTeam1-=pts;
  WritePoints(pointTeam1, pointTeam2);
}

void SumarTeam2(int pts){
  pointTeam2+=pts;
  WritePoints(pointTeam1, pointTeam2);
  tone(buzzer, 800, 80);
}

void RestarTeam2(int pts){
  if (pointTeam2 > 0) pointTeam2-=pts;
  WritePoints(pointTeam1, pointTeam2);
 
}
void ControlTeam1(){
  //   LECTURA BOTÓN TEAM 1
  bool currentState1 = digitalRead(Team1);

  // Pulsar boton: (HIGH -> LOW)
  if (lastState1 == HIGH && currentState1 == LOW) {
    pressTeam1 = millis();
  }

  // Cuando se suelta (LOW -> HIGH)
  if (lastState1 == LOW && currentState1 == HIGH) {
    unsigned long duration = millis() - pressTeam1;
    if (duration >= longPressTime) {
      // PULSACIÓN LARGA TEAM 1 
      if(pointTeam1<14) RestarTeam1(1);
      else RestarTeam1(2);
    } else {
      // PULSACIÓN CORTA TEAM 1 
      if(pointTeam1<12) SumarTeam1(1);
	  else SumarTeam1(2);
    }
  }
  lastState1 = currentState1;
	
}

void ControlTeam2(){
 //   LECTURA BOTÓN TEAM 2

  bool currentState2 = digitalRead(Team2);

  if (lastState2 == HIGH && currentState2 == LOW) {
    pressTeam2 = millis();
  }

  if (lastState2 == LOW && currentState2 == HIGH) {
    unsigned long duration = millis() - pressTeam2;

    if (duration >= longPressTime) {
      //  PULSACIÓN LARGA TEAM 2 
     if(pointTeam1<14) RestarTeam2(1);
      else RestarTeam2(2);
    } else {
      //  PULSACIÓN CORTA TEAM 2 
     if(pointTeam1<12) SumarTeam2(1);
	  else SumarTeam2(2);
    }
  }

  lastState2 = currentState2;
	
}
void WritePoints(int pts1, int pts2){
 /* ESTO MUEVE EL CURSOR (CURSOR DONDE SE VA A ESCRIBIR)
	A X => HORIZONTAL de 0 a 15 (0 EL PRIMER CUADRADO, 15 EL ÚLTIMO CUADRADITO) Y => VERTTICAL 0 O 1*/
  lcd.setCursor(0, 0);
  lcd.print("EQUIP1 | EQUIP2");
  lcd.setCursor(2, 1); 
  lcd.print(String(pointTeam1)); //Hay que añadir el string(variable) para que imprima (Por casteo de variable). 
  lcd.setCursor(7, 1);
  lcd.print("|");
  lcd.setCursor(11, 1);
  lcd.print(String(pointTeam2));
} 
