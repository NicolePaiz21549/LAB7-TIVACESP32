//***********************************************************************************
//Universidad del Valle de Guatemala
//BE3029 - Electrónica Digital 2
//Dulce Nicole Monney Paiz, 21549
//Laboratorio 7 - TIVA C & ESP32 
//***********************************************************************************

//Librerías
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
//***********************************************************************************

//Configuración de la dirección LCD en 0x27 para una pantalla de 16 caracteres y 2 líneas
LiquidCrystal_I2C lcd(0x27, 16, 2); 
//***********************************************************************************

//Definición de pines
#define RXp2 16
#define TXp2 17
#define ROJO 34 
//***********************************************************************************

//Variables globales
uint8_t valor_contador; //Variable para el contador de 8 bits
int receivedvalue1 = 0;
int receivedvalue2 = 0;
//***********************************************************************************

//Configuración
//***********************************************************************************
void setup(){
    Serial.begin(115200); //Comunicación con el monitor serial/PC
    Serial2.begin(115200, SERIAL_8N1, RXp2, TXp2); //Comunicación UART 2 con Tiva C
    
    lcd.init(); //Inicialización de la pantalla LCD para usar pines I2C definidos
    lcd.backlight();
}

//Loop principal
//***********************************************************************************
void loop(){
    if (Serial2.available()) {
      receivedvalue1 = Serial2.parseInt();
      Serial.print("AZUL: ");
      Serial.println(receivedvalue1);

      receivedvalue2 = Serial2.parseInt();
      Serial.print("VERDE: ");
      Serial.println(receivedvalue2);
  }

  //Lectura y visualización del valor ROJO - Conversión Analógica a contador de 8-bits
  int valor_analogico = analogRead(ROJO); //Escalar el valor analógico al rango de 0 a 255
  valor_contador = map(valor_analogico, 0, 4096, 0, 255); //Rango de lectura
 
//Condicionales para evitar la sobreescritura de dígitos en los contadores (ROJO, VERDE & AZUL)
//CONTADOR ROJO
if(valor_contador>=10 && valor_contador<=99){ //DECENAS A CENTENAS Y VICEVERSA
  //Si el valor está entre 10 y 99, se agrega un espacio en el tercer dígito
  lcd.setCursor(2, 1); //Posición del tercer dígito
  lcd.print("          ");
  } 

if (valor_contador>=0 && valor_contador<=9){ //UNIDADES A DECENAS Y VICEVERSA
  //Si el valor está entre 0 y 9, se agrega un espacio encima de los primeros dos dígitos
  lcd.setCursor(1, 1); //Posición de los dos primeros dos dígitos
  lcd.print("          ");
}

//CONTADOR VERDE
if(receivedvalue2>=10 && receivedvalue2<=99){ //DECENAS A CENTENAS Y VICEVERSA
  //Si el valor está entre 10 y 99, se agrega un espacio en el tercer dígito
  lcd.setCursor(7, 1); //Posición del tercer dígito
  lcd.print("          ");
  } 

if (receivedvalue2>=0 && receivedvalue2<=9){ //UNIDADES A DECENAS Y VICEVERSA
  //Si el valor está entre 0 y 9, se agrega un espacio encima de los primeros dos dígitos
  lcd.setCursor(6, 1); //Posición de los dos primeros dos dígitos
  lcd.print("          ");
}

//CONTADOR AZUL
if(receivedvalue1>=10 && receivedvalue1<=99){ //DECENAS A CENTENAS Y VICEVERSA
  //Si el valor está entre 10 y 99, se agrega un espacio en el tercer dígito
  lcd.setCursor(13, 1); //Posición del tercer dígito
  lcd.print("          ");
  } 

if (receivedvalue1>=0 && receivedvalue1<=9){ //UNIDADES A DECENAS Y VICEVERSA
  //Si el valor está entre 0 y 9, se agrega un espacio encima de los primeros dos dígitos
  lcd.setCursor(12, 1); //Posición de los dos primeros dos dígitos
  lcd.print("          ");
}
//***********************************************************************************

  //Impresión en LCD del POT1/ROJO
  lcd.setCursor(0, 0); 
  lcd.print("ROJO"); 
  lcd.setCursor(0, 1); 
  lcd.print(valor_contador);
  delay(20);

  //Impresión en LCD del CPU/VERDE recibido de la Tiva C
  lcd.setCursor(5, 0); 
  lcd.print("VERDE"); 
  lcd.setCursor(5, 1); 
  lcd.print(receivedvalue2);
  delay(20);

  //Impresión en LCD del POT2/AZUL recibido de la Tiva C
  lcd.setCursor(11, 0); 
  lcd.print("AZUL"); 
  lcd.setCursor(11, 1); 
  lcd.print(receivedvalue1);
  delay(20);
}
