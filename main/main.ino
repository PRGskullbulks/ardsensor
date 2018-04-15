/*VARIABLES INTERNAS
 * V
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
 const int pinLM35 = 0; // Variable del pin de entrada del sensor (A0)
 
/*ELECTROVALVULAS
 * 
 * Se simularán con interruptores pero la idea es usar el ADC para leer los caudales, ya que se requiere full caudal
 * para que estas activen la resistencia
 */

const pinValEnt = 1; //simulación de la electroválvula de entrada de agua (pin 1)
const pinValSal = 2; //simulación de la electroválvula de salida de agua (pin 2)

/*RESISTENCIA DE SALIDA
 * La resistencia de salida se activará de acuerdo a las siguientes características:
 * 
 * + Las electroválvulas detecten full caudal
 * + 
 */
void setup() {
  // Configuramos el puerto serial a 9600 bps
  Serial.begin(9600);
 
}
 
void loop() {
  // Con analogRead leemos el sensor, recuerda que es un valor de 0 a 1023
  tempC = analogRead(pinLM35); 
   
  // Calculamos la temperatura con la fórmula
  tempC = (5.0 * tempC * 100.0)/1024.0; 
 
  // Envia el dato al puerto serial
  Serial.print(tempC);
  // Salto de línea
  Serial.print("\n");
  
  // Esperamos un tiempo para repetir el loop
  delay(1000);

