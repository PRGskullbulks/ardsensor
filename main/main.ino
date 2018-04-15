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
 const int pot1 = 1;
 const int pot2 = 2;
 const int ledP = 13;
 
/*ELECTROVALVULAS
 * 
 * Se simularán con interruptores pero la idea es usar el ADC para leer los caudales, ya que se requiere full caudal
 * para que estas activen la resistencia
 */

int pinValEnt = 3; //simulación de la electroválvula de entrada de agua (pin 1)
int pinValSal = 4; //simulación de la electroválvula de salida de agua (pin 2)
int valTmpSen = 0;
int valElcEnt = 0;
int valElcSal = 0;
int valTmpMed = 0;
/*RESISTENCIA DE SALIDA
 * La resistencia de salida se activará de acuerdo a las siguientes características:
 * 
 * + Las electroválvulas detecten full caudal
 * + la temperatura del agua esté por debajo de los 40°C
 */
void setup() {
  //pinMode(pinValEnt, INPUT_PULLUP);
  pinMode(pinValEnt, INPUT);
  pinMode(pinValSal, INPUT);
  pinMode(ledP,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pinValEnt), setPul1, HIGH);
  attachInterrupt(digitalPinToInterrupt(pinValSal), setPul2, HIGH);
  Serial.begin(9600);
}
 
void loop() {
  digitalWrite(ledP,LOW);
  // Con analogRead leemos el sensor, recuerda que es un valor de 0 a 1023
  //tempC = analogRead(pinLM35); 
   
  // Calculamos la temperatura con la fórmula
  //tempC = (2.0 * tempC * 100.0)/1024.0;
  valTmpSen = analogRead(pinLM35);
  valTmpMed = (0.42 * valTmpSen * 100.0)/1024.0;
  if(valTmpMed <= 40) {
   digitalWrite(ledP,HIGH);
  }
  //Serial.print(" valor voltaje :");
  //Serial.print(valTmpSen);
  //Serial.print("Temperatura: ");
  //Serial.print(valTmpMed);
  //Serial.print(" valor pin 1: ");
  //Serial.print(pinValEnt);
  //Serial.print(" valor pin 2: ");
  //Serial.println(".");
  delay(100);
}

void setPul1()
{
  valElcEnt = 1;
}

void setPul2()
{
  valElcSal = 1;
}

