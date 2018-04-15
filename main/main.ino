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
 
/*ELECTROVALVULAS
 * 
 * Se simularán con interruptores pero la idea es usar el ADC para leer los caudales, ya que se requiere full caudal
 * para que estas activen la resistencia
 */

int pinValEnt = 3; //simulación de la electroválvula de entrada de agua (pin 1)
int pinValSal = 4; //simulación de la electroválvula de salida de agua (pin 2)
int valTmpSen = 0;
/*RESISTENCIA DE SALIDA
 * La resistencia de salida se activará de acuerdo a las siguientes características:
 * 
 * + Las electroválvulas detecten full caudal
 * + la temperatura del agua esté por debajo de los 40°C
 */
void setup() {
  pinMode(pinValEnt, INPUT_PULLUP);
  pinMode(pinValSal, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinValEnt), setPul1, LOW);
  attachInterrupt(digitalPinToInterrupt(pinValSal), setPul2, LOW);
  Serial.begin(9600);
}
 
void loop() {
  // Con analogRead leemos el sensor, recuerda que es un valor de 0 a 1023
  //tempC = analogRead(pinLM35); 
   
  // Calculamos la temperatura con la fórmula
  tempC = (5.0 * tempC * 100.0)/1024.0;
  valTmpSen = analogRead(pinLM35);
  Serial.print(valTmpSen);
  Serial.println(" valor voltaje");
  delay(500);
}

void setPul1()
{
  delay(1);
}

void setPul2()
{
  delay(1);
}

