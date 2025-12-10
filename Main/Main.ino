#include <LiquidCrystal_I2C.h>

//Configuración componentes
	//LCD
LiquidCrystal_I2C lcd(0x20,16,2);
	//LEDS
const int ledTeam1 =3;
const int ledTeam2 =4;
	//Buzzer
const int buzzer=5; 
	//Pulsadores
const int Team1=6; 
const int Team2=7; 

//variables
int pointTeam1=0;
int pointTeam2=0;



void setup()
{
 lcd.init();         // Inicializa la pantalla LCD
  lcd.backlight();
  lcd.setCursor(0, 0); 
  lcd.print("Empieza");
  lcd.setCursor(0, 1);
  lcd.print("el partido!");
  
}

void loop()
{
 
}