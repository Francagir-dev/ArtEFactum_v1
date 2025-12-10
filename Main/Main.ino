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
int pointTeam1=0;
int pointTeam2=0;


void setup()
{
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
 
}
void SetTeam1Pts(){
}
void SetTeam2Pts(){
}
void WritePoints(int pts1, int pts2){
  lcd.setCursor(0, 0); 
  lcd.print("PARTIDO");
  lcd.setCursor(0, 1);
  lcd.print("Eq1: "+String(pts1)+ "  "+ "Eq2:"+String(pts2)); //Hay que añadir el string(variable) para que imprima
} 