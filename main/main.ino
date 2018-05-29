/*
 * LIBRERIA PARA EL DISPLAY DE CRISTAL LIQUIDO DE 2X16
 * 
 */

#include <LiquidCrystal.h>

/*VARIABLES INTERNAS
 * 
 * 
 * Documentación de variables internas:
 * + tempC: Temperatura leída del LM35, esta será en grados centígrados
 * 
 */
float tempC; // Variable para almacenar el valor obtenido del sensor (0 a 1023)

/*
 * SENSOR LM35
 * Inicialmente simularemos el umbral de temperatura con LM35, pero esto usará
 * una termocupla, lo conectamos al pin A0
 */
 const int pinLM35 = 0; // sensor de temperatura
 const int ledP = 13;
 const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
 const int pinValEnt = 8; //simulación de la electroválvula de entrada de agua (pin 1 DIPSW)
 const int pinValSal = 9; //simulación de la electroválvula de salida de agua (pin 2 DIPSW)
 LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
/*ELECTROVALVULAS
 * 
 * Se simularán con interruptores pero la idea es usar el ADC para leer los caudales, ya que se requiere full caudal
 * para que estas activen la resistencia
 */

int intResSta = 0; //estado de la resistencia.
int valTmpSen = 0; //Variable temporal del sensor
int valElcEnt = 0; //valor del pin sensor de entrada de agua
int valElcSal = 0; //valor del pin sensor de salida de agua
int valTmpMed = 0; //temperatura medida
int tmpThrVal = 0; //umbral de temperatura del agua

/*RESISTENCIA DE SALIDA
 * La resistencia de salida se activará de acuerdo a las siguientes características:
 * 
 * + Las electroválvulas detecten full caudal
 * + la temperatura del agua esté por debajo de los 40°C
 */
void setup() {                        //funcion setup de inicialización exigido por arduino
  pinMode(pinValEnt, INPUT_PULLUP);   //pin de tipo entrada flanco de subida
  pinMode(pinValSal, INPUT);          //pin de tipo entrada
  pinMode(ledP,OUTPUT);               //pin salida
  Serial.begin(9600);
  lcd.begin(16, 2);                   //inicialización del lcd
  lcd.print("Bienvenido...");         //mensaje de bienvenida
  delay(5000);                        //espera 5 segundos.
}
 
void loop() {
 lcd.clear();  
 lcd.setCursor(0,0);
 lcd.print("Temperatura: ");
 leer_temperatura();
}

int leer_temperatura (){
  tmpThrVal = 40;
  valTmpSen = analogRead(pinLM35);
  valElcEnt = ! digitalRead(pinValEnt);
  valElcSal = ! digitalRead(pinValSal);
  lcd.setCursor(0,1);
  valTmpMed = (0.51 * valTmpSen * 100.0)/1024.0;
  lcd.print(valTmpMed);
  lcd.print(" grados C");

  if(valTmpMed <=tmpThrVal &&  valElcEnt ==1 &&  valElcSal ==1 )
  {
   digitalWrite(ledP,HIGH);
   intResSta = 1;
   delay(500);

  }
  else {
    digitalWrite(ledP,LOW);
    intResSta = 0;
    delay(500);
  }
  
  
}


