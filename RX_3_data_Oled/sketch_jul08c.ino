#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
 
//Declaremos los pines CE y el CSN
#define CE_PIN 10
#define CSN_PIN 9
 
//Variable con la dirección del canal que se va a leer
byte direccion[5] ={'c','a','n','a','l'}; 

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector para los datos recibidos
float datos[3];

void setup()
{
  
  //inicializamos el puerto serie
 // Serial.begin(9600); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  // display.display();
 // delay(2000);
   radio.begin();
  //Abrimos el canal de Lectura
  radio.openReadingPipe(1, direccion);
  
    //empezamos a escuchar por el canal
  radio.startListening();
 

 // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(WHITE);
 
}
 
void loop() {
  
  //inicializamos el NRF24L01 
  uint8_t numero_canal;
 //if ( radio.available(&numero_canal) )
 if ( radio.available() )
 {    
     //Leemos los datos y los guardamos en la variable datos[]
     radio.read(datos,sizeof(datos));
     display.setCursor(0, 0);
     //reportamos  los datos recibidos
     display.print("Dato0= " );
     display.print(datos[0]);
     display.print(" V, ");
     display.print("Dato1= " );
     display.print(datos[1]);
     display.print(" ms, ");
     display.print("Dato2= " );
     display.print(datos[2]);
    display.display(); // tell display to...display
  delay(2000);
  display.clearDisplay();
}
}
