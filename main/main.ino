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
 
void loop() {                         //Funcion principal
 lcd.clear();                         //limpieza LCD
 lcd.setCursor(0,0);                  //poner cursor en la primera linea
 lcd.print("Temperatura: ");          //imprimir temperatura
 leer_temperatura();                  //ejecutar función leer temperatura
}

int leer_temperatura (){              //inicia funcion leer temperatura 
  tmpThrVal = 40;                     //se coloca el umbral de apagar / prender el calor en 40 grados
  valTmpSen = analogRead(pinLM35);    //se lee el valor del sensor de temperatura
  valElcEnt = ! digitalRead(pinValEnt); //Revisar si el sensor de entrada del agua está activo
  valElcSal = ! digitalRead(pinValSal); //Revisar si el sensor de salida del agua está activo
  lcd.setCursor(0,1);                   //ubicar el LCD en la segunda línea
  valTmpMed = (0.51 * valTmpSen * 100.0)/1024.0;  //temperatura = valor leído *100 /1024
  lcd.print(valTmpMed);                   //escribir el valor de la temperatura de la LCD
  lcd.print(" grados C");                 

  if(valTmpMed <=tmpThrVal &&  valElcEnt ==1 &&  valElcSal ==1 )
  {
   digitalWrite(ledP,HIGH);    //si las valvulas están activas  y la temperatura está por debajo del umbral prender la resistencia
   intResSta = 1;               //estado resistencia en 1
   delay(500);                 //Espera medio segundo

  }
  else {
    digitalWrite(ledP,LOW);  //valvulas sin agua, apagar la resistencia
    intResSta = 0;            //Resistencia en 0
    delay(500);               //Esperar medio segundo
  }
  
  
}


