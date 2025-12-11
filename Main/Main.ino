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
const int Team1=6; 
const int Team2=7; 

//variables
int pointTeam1=3;
int pointTeam2=12;

// --- Variables para pulsación larga/corta ---
unsigned long pressTeam1 = 0;
unsigned long pressTeam2 = 0;

bool lastState1 = HIGH;  
bool lastState2 = HIGH;

const unsigned long longPressTime = 700;  // 700 ms → pulsación larga


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
  lcd.clear();  //ACORDAROS DE ESTA LINEA PARA LIMPIAR LA PANTALLA ANTES DE AÑADIR MÁS COSAS O NUEVAS
   WritePoints(pointTeam1, pointTeam2);
}

void loop()
{
  
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
      RestarTeam1();
    } else {
      // PULSACIÓN CORTA TEAM 1 
      SumarTeam1();
    }
  }

  lastState1 = currentState1;



  //   LECTURA BOTÓN TEAM 2

  bool currentState2 = digitalRead(Team2);

  if (lastState2 == HIGH && currentState2 == LOW) {
    pressTeam2 = millis();
  }

  if (lastState2 == LOW && currentState2 == HIGH) {
    unsigned long duration = millis() - pressTeam2;

    if (duration >= longPressTime) {
      //  PULSACIÓN LARGA TEAM 2 
      RestarTeam2();
    } else {
      //  PULSACIÓN CORTA TEAM 2 
      SumarTeam2();
    }
  }

  lastState2 = currentState2;
}
void SumarTeam1(){
  pointTeam1++;
  WritePoints(pointTeam1, pointTeam2);
  tone(buzzer, 800, 80);
}

void RestarTeam1(){
  if (pointTeam1 > 0) pointTeam1--;
  WritePoints(pointTeam1, pointTeam2);

}

void SumarTeam2(){
  pointTeam2++;
  WritePoints(pointTeam1, pointTeam2);
  tone(buzzer, 800, 80);
}

void RestarTeam2(){
  if (pointTeam2 > 0) pointTeam2--;
  WritePoints(pointTeam1, pointTeam2);
 
}
void WritePoints(int pts1, int pts2){
  lcd.setCursor(0, 0); 
  lcd.print("PARTIDO");
  lcd.setCursor(0, 1);
  lcd.print("Eq1: "+String(pts1)+ "  "+ "Eq2:"+String(pts2)); //Hay que añadir el string(variable) para que imprima
} 