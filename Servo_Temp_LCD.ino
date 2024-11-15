
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int analogIn = A1;
const int servopin = 9; 
const int LED = 10; 
int temperaturelimit = 25; 
int temperaturelimitserial = -1; 

int RawValue = 0;
double voltage = 0;
double tempc = 0;
double tempF = 0;

Servo Servo1;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT); 
  Servo1.attach(servopin);
  lcd.init();
  lcd.backlight();

 
  lcd.setCursor(0, 0); 
  lcd.print("Sistema listo");
  delay(2000);
  lcd.clear(); 
}

void loop() {
  
  if (Serial.available() > 0) {
    temperaturelimitserial = Serial.parseInt(); 
    Serial.println("Valor recibido:");
    Serial.println(temperaturelimitserial);
  }

  
  RawValue = analogRead(analogIn);
  voltage = (RawValue / 1023.0) * 5000; 
  tempc = voltage * 0.1; 
  tempF = (tempc * 1.8) + 32; 

  
  lcd.setCursor(0, 0);
  lcd.print("Temp (C): ");
  lcd.setCursor(0, 1); 
  lcd.print(tempc, 1);

  Serial.print("Temperatura (C): ");
  Serial.println(tempc, 1);

  
  int currentLimit = (temperaturelimitserial != -1) ? temperaturelimitserial : temperaturelimit;

  
  if (tempc > currentLimit) {
    digitalWrite(LED, HIGH); 
    Servo1.write(0);
    delay(1000);
    Servo1.write(90);
    delay(1000);
    Servo1.write(180);
    delay(1000);
  } else {
    digitalWrite(LED, LOW); 
    Servo1.write(90); 
  }

  delay(500); 
}
