#include <rgb_lcd.h>
#include <Wire.h>
#include <DHT.h>

// Constantes , a changer selon l'envie:
const int BUTTON_PIN = 3; // La pin du bouton
const int SHORT_PRESS_TIME = 1000; // 1000 millisecondes
const int LONG_PRESS_TIME = 3000; // 3000 millisecondes
const int NO_PRESS_TIME = 0; // 0 milliseconds (C'est une pression btw)


// Variables qui changent:
int lastState = LOW; 
int currentState;     
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;
long pressDuration = releasedTime - pressedTime;




rgb_lcd LCD_RGB;
DHT dht_2_DHT22(2,DHT22);


void setup() {
  LCD_RGB.begin(16, 2);
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(3, INPUT);
dht_2_DHT22.begin();
}




void loop() {
  // état du bouton 
  currentState = digitalRead(BUTTON_PIN);

  if(lastState == HIGH && currentState == LOW)        // bouton pressé
    pressedTime = millis();
  else if(lastState == LOW && currentState == HIGH) { // bouton relaché
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;

      if( pressDuration < NO_PRESS_TIME )
      LCD_RGB.clear(); //Bloc pour Horloge
      LCD_RGB.clear();
      LCD_RGB.setCursor(0,0);
      LCD_RGB.print("Temps Restant:");
      LCD_RGB.setCursor(7,1);
      LCD_RGB.print((int)(dht_2_DHT22.readHumidity()));
      delay(10000);


      if( pressDuration < SHORT_PRESS_TIME )
      LCD_RGB.clear();
      LCD_RGB.clear();
      LCD_RGB.setCursor(0,0);
      LCD_RGB.print("Temperature:");
      LCD_RGB.setCursor(7,1);
      LCD_RGB.print((int)(dht_2_DHT22.readTemperature()));
      delay(10000);


      if( pressDuration < LONG_PRESS_TIME )
      LCD_RGB.clear(); //Bloc pour Humidité
      LCD_RGB.clear();
      LCD_RGB.setCursor(0,0);
      LCD_RGB.print("Taux D\' humidite:");
      LCD_RGB.setCursor(7,1);
      LCD_RGB.print((int)(dht_2_DHT22.readHumidity()));
      delay(10000);


  }

  // save the the last state
  lastState = currentState;
}